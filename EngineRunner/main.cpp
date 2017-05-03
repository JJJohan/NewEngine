#include <cstdlib>
#include "../Engine/Utils/Logger.h"
#include "../Engine/Core/Core.h"
#include "../Engine/Core/Time.h"
#include "../Engine/Utils/Console.h"
#include "Utils/SystemInfo.h"

using namespace Engine;

class Game
{
public:
	Game();

	void Start();
	void Update() const;
	void Draw() const;
	void Destroy() const;
};

Game::Game()
{
}

void Game::Start()
{
}

void Game::Update() const
{
}

void Game::Draw() const
{
}

void Game::Destroy() const
{
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
#ifdef _DEBUG
	Console::InitConsole();
#endif

	Logger::Instance()->Log("Starting engine...\n");
	
	float timer = 0.0f;

	Core core;
	//Core::Initialise(1024, 768, true, engineLink);
	//Core::SetMaxFPS(300);

	//SystemInfo::PrintSystemInfo();

	while (core.Running())
	{
		if (core.Update() != EXIT_SUCCESS)
		{
			// Update returned false, exit.
			break;
		}

		float dt = Time::Instance()->DeltaTime();
		timer += dt;
		if (timer > 0.1f)
		{
			String title = String::Format("Engine - CPU: {0} FPS", int(1 / dt));
			Console::SetTitle(title);
			timer -= 0.1f;
		}
	}

	Logger::Instance()->Log("\n\nDestroying engine...");

	core.Shutdown();

	Logger::Instance()->Log("Engine destroyed");

	return EXIT_SUCCESS;
}
