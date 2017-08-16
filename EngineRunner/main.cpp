#include <cstdlib>
#include "../Engine/Utils/Logger.h"
#include "../Engine/Core/Core.h"
#include "../Engine/Utils/Console.h"
#include "../Engine/Core/Lua.h"
#include "../Engine/Utils/SystemInfo.h"
#include "../Engine/Rendering/SceneManager.h"
#include "Rendering/GameObject.h"
#include "Rendering/ICamera.h"
#include "Rendering/IMesh.h"
#include "Data/Colour.h"

using namespace Engine;

Core core;
Scene* scene;
ICamera* camera;

void Start()
{
	Logger::Instance()->Log("Starting engine...\n");

	//Lua::Instance()->Load(Core::Instance()->GetApplicationDirectory() + "game.lua");

	core.Initialise(1024, 768, false, "D3D11");
	core.SetMaxFPS(60);
	SystemInfo::Instance()->PrintSystemInfo();

	scene = SceneManager::Instance()->CreateScene();

	GameObject* go = new GameObject("Main Camera");
	camera = go->AddComponent<ICamera>();
}

void Update()
{

}

void Render()
{
	camera->Render();
}

void Shutdown()
{
	
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{		
	Start();
	core.OnUpdate += Update;
	core.OnRender += Render;

	while (core.Running())
	{
		if (core.Update() != EXIT_SUCCESS)
		{
			// Update returned false, exit.
			break;
		}
	}

	Shutdown();
	core.Shutdown();

	Logger::Instance()->Log("Engine destroyed");

	return EXIT_SUCCESS;
}