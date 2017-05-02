#pragma once
#include "Common.h"

namespace Engine
{
	class Core;

	class Time
	{
	public:
		static ENGINE_API float DeltaTime();
		static ENGINE_API float RunningTime();
		static ENGINE_API float GPUTime();
		static ENGINE_API void Sleep(float seconds);

		static void Initialise();
		static void Update();

	private:
		static void ResetCPUCounter();
		static void SetGPUDelta(float delta);

		static float _deltaTime;
		static float _runningTime;
		static float _gpuTime;
		static double _frequency;
		static double _cpuCounter;
	};
}
