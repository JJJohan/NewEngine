#pragma once

#include "CPU/Processor.h"
#include "../Core/Common.h"
#include <mutex>
#include "../Core/IRegisteredClass.h"

namespace Engine
{
	class Vector2;

	class SystemInfo : IRegisteredClass
	{
	public:
		ENGINE_API void PrintSystemInfo();
		ENGINE_API Vector2 GetNativeResolution();
		ENGINE_API int GetCPUCores();
		static ENGINE_API SystemInfo* Instance();
		void Register() override;

	private:
		SystemInfo();
		~SystemInfo();
		std::string GetOSInfo();
		std::string GetCPUInfo();
		std::string GetGPUInfo();
		std::string GetMemInfo();
		std::string GetDisplayInfo();
		std::string GetFileVersion(const std::string& fileName);
		Processor _processor;
		static SystemInfo* _pInstance;
		std::mutex _mutex;
	};
}
