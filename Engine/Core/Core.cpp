#include "Core.h"
#include "Time.h"
#include "../Input/Input.h"
#include "Lua.h"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include "../Utils/Logger.h"

namespace Engine
{
	Core* Core::_pInstance = nullptr;
	String Core::_appDirectory;

	Core::Core()
		: _running(true)
		, _maxFps(0)
	{
		_pInstance = this;

		_pLua = Lua::Instance();
		_pTime = Time::Instance();
		_pInput = Input::Instance();

		_pLua->Load(GetApplicationDirectory() + "game.lua");

		_pInput->RegisterKey(VK_ESCAPE, KeyDown, [=]
		{
			Shutdown();
		}, "__exit");
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
		OnUpdate.Call();
		
		if (_maxFps > 0)
		{
			_pTime->Sleep(1.0f / _maxFps - _pTime->DeltaTime());
		}

		return EXIT_SUCCESS;
	}

	void Core::Initialise(int width, int height, bool windowed)
	{
		Logger::Instance()->Log("Width: {0}", width);
		Logger::Instance()->Log("Height: {0}", height);
		Logger::Instance()->Log("Windowed: {0}", windowed);
	}

	void Core::Shutdown()
	{
		OnShutdown.Call();
		_running = false;
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

			size_t seperatorIndex = _appDirectory.Str().find_last_of('\\');
			if (seperatorIndex != -1)
			{
				_appDirectory = _appDirectory.Str().substr(0, seperatorIndex + 1);
			}
		}

		return _appDirectory;
	}
}
