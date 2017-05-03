#pragma once
#include "Common.h"

namespace Engine
{
	class Core;

	class Time
	{
	public:
		ENGINE_API float DeltaTime() const;
		ENGINE_API float RunningTime() const;
		ENGINE_API float GPUTime() const;
		ENGINE_API void Sleep(float seconds);

		void Update();
		static ENGINE_API Time* Instance();

	private:
		Time();
		~Time();
		void ResetCPUCounter();
		void SetGPUDelta(float delta);

		static Time* _pInstance;
		float _deltaTime;
		float _runningTime;
		float _gpuTime;
		double _frequency;
		double _cpuCounter;
	};
}
