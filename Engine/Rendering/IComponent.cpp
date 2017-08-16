#include "IComponent.h"
#include "GameObject.h"

namespace Engine 
{
	IComponent::IComponent(GameObject* owner)
		: _pOwner(owner)
		, Enabled(true)
	{
	}
	
	IComponent::~IComponent()
	{
	}

	void IComponent::Destroy()
	{
		_pOwner->RemoveComponent(this);
	}
}