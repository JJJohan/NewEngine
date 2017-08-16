#include "Time.h"
#include "../Core/Core.h"
#include <thread>
#include "../Utils/Logger.h"

namespace Engine
{
	const float TimeEpsilon = 0.0f;

	Time* Time::_pInstance = nullptr;

	Time::Time()
		: _deltaTime(0.0f)
		, _runningTime(0.0f)
		, _gpuTime(0.0f)
		, _frequency(0.0)
		, _cpuCounter(0.0)
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
		{
			Logger::Instance()->LogError("QueryPerformanceFrequency failed!");
		}

		_frequency = double(li.QuadPart);

		QueryPerformanceCounter(&li);
		_cpuCounter = double(li.QuadPart);

		Core::Instance()->OnUpdate += std::bind(&Time::Update, this);
		Core::Instance()->OnShutdown += std::bind(&Time::Shutdown);
	}

	void Time::Shutdown()
	{
		if (_pInstance != nullptr)
		{
			delete _pInstance;
			_pInstance = nullptr;
		}
	}
	
	Time* Time::Instance()
	{
		if (_pInstance == nullptr)
		{
			_pInstance = new Time();
		}

		return _pInstance;
	}

	void Time::ResetCPUCounter()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		_cpuCounter = double(li.QuadPart);
	}

	float Time::DeltaTime() const
	{
		if (_deltaTime > 10.0f)
		{
			return 10.0f;
		}

		return _deltaTime;
	}

	float Time::RunningTime() const
	{
		return _runningTime;
	}

	float Time::GPUTime() const
	{
		return _gpuTime;
	}

	void Time::Sleep(float seconds)
	{
		LARGE_INTEGER freq, begin, end;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&begin);
		QueryPerformanceCounter(&end);
		const __int64 waitTime = __int64(freq.QuadPart * seconds);
		while (end.QuadPart - begin.QuadPart < waitTime)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			QueryPerformanceCounter(&end);
		}
	}

	void Time::Update()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);

		// Calculate frame time
		_deltaTime = float(float(li.QuadPart - _cpuCounter) / _frequency);
		_runningTime += _deltaTime;

		ResetCPUCounter();
	}

	void Time::SetGPUDelta(float delta)
	{
		_gpuTime = delta;
	}
}
