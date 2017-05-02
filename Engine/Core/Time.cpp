#include "Time.h"
#include "../Utils/Logging.h"
#include <thread>

namespace Engine
{
	float Time::_deltaTime = 0.0f;
	float Time::_runningTime = 0.0f;
	float Time::_gpuTime = 0.0f;
	double Time::_frequency = 0.0;
	double Time::_cpuCounter = 0.0;

	const float TimeEpsilon = 0.0f;

	void Time::Initialise()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
		{
			Logging::LogError("QueryPerformanceFrequency failed!");
		}

		_frequency = double(li.QuadPart);

		QueryPerformanceCounter(&li);
		_cpuCounter = double(li.QuadPart);
	}

	void Time::ResetCPUCounter()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		_cpuCounter = double(li.QuadPart);
	}

	float Time::DeltaTime()
	{
		if (_deltaTime > 10.0f)
		{
			return 10.0f;
		}

		return _deltaTime;
	}

	float Time::RunningTime()
	{
		return _runningTime;
	}

	float Time::GPUTime()
	{
		return _gpuTime;
	}

	void Time::Sleep(float seconds)
	{
		LARGE_INTEGER freq, begin, end;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&begin);
		QueryPerformanceCounter(&end);
		__int64 waitTime = freq.QuadPart * seconds;
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
		_deltaTime = float(li.QuadPart - _cpuCounter) / _frequency;
		_runningTime += _deltaTime;

		ResetCPUCounter();
	}

	void Time::SetGPUDelta(float delta)
	{
		_gpuTime = delta;
	}
}
