#include <cstdlib>
#include "../Engine/Utils/Logging.h"
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

	Logging::Log("Starting engine...\n");
	
	float timer = 0.0f;
	Game game;
	ENGINE_LINK_DESC engineLink =
	{
		std::bind(&Game::Start, &game),
		std::bind(&Game::Update, &game),
		std::bind(&Game::Draw, &game),
		std::bind(&Game::Destroy, &game)
	};

	Core::Initialise(1024, 768, true, engineLink);
	Core::SetMaxFPS(300);

	SystemInfo::PrintSystemInfo();

	while (Core::Running())
	{
		if (Core::Update() != EXIT_SUCCESS)
		{
			// Update returned false, exit.
			break;
		}

		timer += Time::DeltaTime();
		if (timer > 0.1f)
		{
			String title = String::Format("Engine - CPU: {0} FPS | GPU: {1} FPS", int(1 / Time::DeltaTime()), int(1 / Time::GPUTime()));
			Console::SetTitle(title);
			timer -= 0.1f;
		}
	}

	Logging::Log("\n\nDestroying engine...");

	Core::Destroy();

	Logging::Log("Engine destroyed");

	return EXIT_SUCCESS;
}
