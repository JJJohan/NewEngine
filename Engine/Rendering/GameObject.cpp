#include "GameObject.h"
#include "IComponent.h"

namespace Engine
{
	GameObject::GameObject(std::string name)
		: Name(name)
	{
		
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < _components.size(); ++i)
		{
			delete _components[i];
		}
		_components.clear();
	}

	void GameObject::RemoveComponent(IComponent* component)
	{
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			IComponent* curr = *it;
			if (curr == component)
			{
				delete component;
				_components.erase(it);
				return;
			}
		}
	}

}