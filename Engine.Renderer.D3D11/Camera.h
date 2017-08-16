#pragma once

#include "../Engine/Rendering/ICamera.h"
#include "../Engine/Data/Colour.h"
#include <d3d11.h>
#include <dxgi.h>

namespace Engine
{
	namespace Renderer
	{
		class Camera : public ICamera
		{
		public:
			Camera(GameObject* owner);
			~Camera();

			void Render() override;
			void SetClearColour(const Colour& colour) override;
			void Initialise(ID3D11Device* device, IDXGISwapChain* swapChain, ID3D11DeviceContext* context);

		private:
			Colour _clearColour;
			FLOAT* _pClearColour;
			ID3D11DeviceContext* _pContext;
			ID3D11RenderTargetView* _pRTV;
		};
	}
}