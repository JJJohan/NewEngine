#pragma once

#include "../Engine/Rendering/IMesh.h"

namespace Engine
{
	namespace Renderer
	{
		class Mesh : public IMesh
		{
		public:
			Mesh(GameObject* owner);
			~Mesh();

			void Render() override;

		private:

		};
	}
}