#pragma once

#include "Common.h"
#include "../Data/String.h"
#include "../Input/Event.h"

namespace Engine
{
	class Lua;
	class Time;
	class Input;

	class Core
	{
	public:
		ENGINE_API Core();
		ENGINE_API ~Core();
		ENGINE_API bool Update();
		ENGINE_API bool Running() const;
		ENGINE_API void Shutdown();
		ENGINE_API void Initialise(int width, int height, bool windowed);
		ENGINE_API void SetMaxFPS(int max);
		ENGINE_API int GetMaxFPS() const;
		static ENGINE_API String GetApplicationDirectory();
		static ENGINE_API Core* Instance();

		Event OnUpdate;
		Event OnRender;
		Event OnShutdown;

	private:
		static Core* _pInstance;
		static String _appDirectory;

		Lua* _pLua;
		Time* _pTime;
		Input* _pInput;
		bool _running;
		int _maxFps;
	};
}
