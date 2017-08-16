#pragma once

#include <vector>
#include "../Core/Common.h"
#include "RenderSystem.h"

namespace Engine
{
	class IComponent;

	class GameObject
	{
	public:
		ENGINE_API GameObject(std::string name);
		ENGINE_API ~GameObject();

		template <class T>
		T* AddComponent()
		{
			T* t = RenderSystem::Instance()->CreateComponent<T>(this);
			_components.push_back(t);
			return t;
		}

		void RemoveComponent(IComponent* component);

		std::string Name;

	private:
		std::vector<IComponent*> _components;
	};
}
