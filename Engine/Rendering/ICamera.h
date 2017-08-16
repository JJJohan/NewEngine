#pragma once
#include "IComponent.h"
#include "../Data/Colour.h"

namespace Engine
{
	class ICamera : public IComponent
	{
	public:
		explicit ICamera(GameObject* owner)
			: IComponent(owner)
		{
		}

		virtual ~ICamera() = default;
		virtual void Render() = 0;
		virtual void SetClearColour(const Colour& colour) = 0;

	protected:
		const Colour DefaultClearColour = Colour(0.153f, 0.31f,	0.494f);
	};
}
