#pragma once

#include "../Core/Common.h"
#include <vector>

namespace Engine
{
	class Scene;

	class SceneManager
	{
	public:
		ENGINE_API static SceneManager* Instance();

		ENGINE_API Scene* CreateScene();
		ENGINE_API void DestroyScene(Scene* scene);

	private:
		SceneManager();
		~SceneManager();
		void Shutdown();

		static SceneManager* _pInstance;
		std::vector<Scene*> _scenes;
	};
}
