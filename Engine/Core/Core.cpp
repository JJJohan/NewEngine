#include <thread>
#include "Core.h"
#include "Time.h"
#include "../Input/Input.h"

namespace Engine
{
	const float TimeEpsilon = 0.0001f;

	std::string Core::_appDirectory = std::string();
	bool Core::_running = true;
	bool Core::_renderThreadAssigned = false;
	int Core::_maxFps;
	std::function<void()> Core::_updateLoop;
	std::function<void()> Core::_destroyMethod;
	std::thread _renderThread = std::thread();

	bool Core::Update()
	{
		Time::Update();
		Input::Update();

		// Call the main update loop.
		_updateLoop();

		if (_maxFps > 0)
		{
			Time::Sleep(1.0f / _maxFps - Time::DeltaTime());
		}

		return EXIT_SUCCESS;
	}

	void Core::Render()
	{
	}

	void Core::Initialise(int width, int height, bool windowed, ENGINE_LINK_DESC engineLink, HWND windowHandle)
	{
		Time::Initialise();

		_updateLoop = engineLink.UpdateLoop;
		_destroyMethod = engineLink.DestroyMethod;

		Input::RegisterKey(VK_ESCAPE, KeyDown, []
		{
			Exit();
		}, "__exit");
	}

	void Core::SetMaxFPS(int max)
	{
		_maxFps = max;
	}

	int Core::GetMaxFPS()
	{
		return _maxFps;
	}

	void Core::Exit()
	{
		_running = false;
	}

	bool Core::Running()
	{
		return _running;
	}

	void Core::Destroy()
	{
		Exit();

		_destroyMethod();

		_updateLoop = nullptr;
		_destroyMethod = nullptr;
	}

	std::string Core::GetApplicationDirectory()
	{
		if (_appDirectory.empty())
		{
			char dir[512];
			GetModuleFileNameA(nullptr, dir, sizeof(dir));
			_appDirectory = std::string(dir);

			size_t seperatorIndex = _appDirectory.find_last_of('\\');
			if (seperatorIndex != -1)
			{
				_appDirectory = _appDirectory.substr(0, seperatorIndex + 1);
			}
		}

		return _appDirectory;
	}
}
