#include "Core.h"
#include "Time.h"
#include "../Input/Input.h"
#include "../Utils/Console.h"
#include "Lua.h"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include "../Utils/Logger.h"
#include "../Utils/SystemInfo.h"
#include "../Rendering/Window.h"
#include "../Rendering/RenderSystem.h"
#include "../Rendering/IRenderer.h"
#include "../Rendering/SceneManager.h"

namespace Engine
{
	Core* Core::_pInstance = nullptr;
	String Core::_appDirectory;

	Core::Core()
		: _pRenderer(nullptr)
		, _running(true)
		, _maxFps(0)
	{
		_pInstance = this;

		Register(this);
		InitSystems();

		_pInput->RegisterKey(VK_ESCAPE, KeyDown, [=]
		{
			Shutdown();
		}, "__exit");
	}

	void Core::Register(IRegisteredClass* registeredClass)
	{
		_registeredClasses.push_back(registeredClass);
	}

	void Core::Register()
	{
		_pLua->RegisterMethod("Core", "Initialise", SmartBind(*this, &Core::Initialise));
		_pLua->RegisterMethod("Core", "SetMaxFPS", SmartBind(*this, &Core::SetMaxFPS));
		_pLua->RegisterMethod("Core", "Shutdown", SmartBind(*this, &Core::Shutdown));
	}

	void Core::InitSystems()
	{
		_pLua = Lua::Instance();

#ifdef _DEBUG
		Console::Instance()->InitConsole();
#endif

		_pTime = Time::Instance();
		_pInput = Input::Instance();
		Logger::Instance();
		SystemInfo::Instance();
		SceneManager::Instance();

		for (IRegisteredClass* registeredClass : _registeredClasses)
		{
			registeredClass->Register();
		}
	}

	Core::~Core()
	{
		if (_running)
		{
			Shutdown();
		}
	}

	bool Core::Update()
	{
		if (!_running)
		{
			return EXIT_SUCCESS;
		}

		OnUpdate.Call();

		if (!_running)
		{
			return EXIT_SUCCESS;
		}

		if (_pRenderer != nullptr)
		{
			_pRenderer->Draw();
		}

		if (_maxFps > 0)
		{
			_pTime->Sleep(1.0f / _maxFps - _pTime->DeltaTime());
		}

		return EXIT_SUCCESS;
	}

	void Core::Initialise(int width, int height, bool fullscreen, std::string rendererName)
	{
		Window::Initialise(width, height, fullscreen);

		if (RenderSystem::Instance()->Initialise(rendererName))
		{
			IRenderer* renderer = RenderSystem::Instance()->Create();
			if (renderer != nullptr)
			{
				renderer->Initialise(width, height, fullscreen, Window::Instance()->Handle);
				_pRenderer = renderer;
			}
		}
	}

	void Core::Shutdown()
	{
		if (_running)
		{
			_running = false;
			_pRenderer = nullptr;
			OnShutdown.Call();
		}
	}

	bool Core::Running() const
	{
		return _running;
	}

	void Core::SetMaxFPS(int max)
	{
		_maxFps = max;
	}

	int Core::GetMaxFPS() const
	{
		return _maxFps;
	}

	Core* Core::Instance()
	{
		return _pInstance;
	}

	String Core::GetApplicationDirectory()
	{
		if (_appDirectory.Length() == 0)
		{
			char dir[512];
			GetModuleFileNameA(nullptr, dir, sizeof(dir));
			_appDirectory = std::string(dir);

			const size_t seperatorIndex = _appDirectory.Str().find_last_of('\\');
			if (seperatorIndex != -1)
			{
				_appDirectory = _appDirectory.Str().substr(0, seperatorIndex + 1);
			}
		}

		return _appDirectory;
	}
}
