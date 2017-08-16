#pragma once

#include "Common.h"
#include "../Data/String.h"
#include "../Input/Event.h"
#include "IRegisteredClass.h"

namespace Engine
{
	class Lua;
	class Time;
	class Input;
	class IRenderer;

	class Core : IRegisteredClass
	{
	public:
		ENGINE_API Core();
		ENGINE_API ~Core();
		ENGINE_API bool Update();
		ENGINE_API bool Running() const;
		ENGINE_API void Shutdown();
		ENGINE_API void Initialise(int width, int height, bool fullscreen, std::string rendererName);
		ENGINE_API void SetMaxFPS(int max);
		ENGINE_API int GetMaxFPS() const;
		ENGINE_API void Register(IRegisteredClass* registeredClass);
		static ENGINE_API String GetApplicationDirectory();
		static ENGINE_API Core* Instance();
		void Register() override;

		Event OnUpdate;
		Event OnRender;
		Event OnShutdown;

	private:
		static Core* _pInstance;
		static String _appDirectory;

		void InitSystems();

		Lua* _pLua;
		Time* _pTime;
		Input* _pInput;
		IRenderer* _pRenderer;
		bool _running;
		int _maxFps;
		std::vector<IRegisteredClass*> _registeredClasses;
	};
}
