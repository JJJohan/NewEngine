#pragma once

#include "../Core/Common.h"

namespace Engine
{
	class GameObject;

	class IComponent
	{
	public:
		ENGINE_API IComponent(GameObject* owner);
		ENGINE_API virtual ~IComponent() = 0;
		ENGINE_API void Destroy();

		bool Enabled;

	protected:
		GameObject* _pOwner;
	};
}
