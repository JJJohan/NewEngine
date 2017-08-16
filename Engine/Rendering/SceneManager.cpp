#include "SceneManager.h"
#include "../Core/Core.h"
#include "Scene.h"
#include "../Utils/Logger.h"
#include "RenderSystem.h"

namespace Engine
{
	SceneManager* SceneManager::_pInstance = nullptr;

	SceneManager::SceneManager()
	{
		Core::Instance()->OnShutdown += std::bind(&SceneManager::Shutdown, this);
	}

	void SceneManager::Shutdown()
	{
		for (int i = 0; i < _scenes.size(); ++i)
		{
			delete _scenes[i];
		}
		_scenes.clear();

		delete _pInstance;
	}
	
	SceneManager::~SceneManager()
	{
		_pInstance = nullptr;
	}

	SceneManager* SceneManager::Instance()
	{
		if (_pInstance == nullptr)
		{
			_pInstance = new SceneManager();
		}

		return _pInstance;
	}

	Scene* SceneManager::CreateScene()
	{
		Scene* scene = new Scene();
		_scenes.push_back(scene);
		return scene;
	}

	void SceneManager::DestroyScene(Scene* scene)
	{
		for (auto it = _scenes.begin(); it != _scenes.end(); ++it)
		{
			Scene* curScene = *it;
			if (curScene == scene)
			{
				delete curScene;
				_scenes.erase(it);
				return;
			}
		}

		Logger::Instance()->LogError("Scene could not be found in scene list.");
	}
}
