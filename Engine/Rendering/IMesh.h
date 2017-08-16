#pragma once
#include "IComponent.h"

namespace Engine
{
	class IMesh : public IComponent
	{
	public:
		explicit IMesh(GameObject* owner)
			: IComponent(owner)
		{
		}

		virtual ~IMesh() = default;
		virtual void Render() = 0;
	};
}
