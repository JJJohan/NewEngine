#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include "../Engine/Rendering/IRenderer.h"
#include <dxgi.h>
#include <d3d11.h>

namespace Engine
{
	class ICamera;
	class IScene;
	class IMesh;
	class GameObject;

	namespace Renderer
	{
		class D3D11 : public IRenderer
		{
		public:
			D3D11();
			~D3D11();

			void Initialise(int width, int height, bool fullscreen, HWND handle) override;
			void Draw() override;

			ICamera* CreateCamera(GameObject* owner) override;

		private:
			IDXGISwapChain* _pSwapChain;
			ID3D11Device* _pDevice;
			ID3D11DeviceContext* _pContext;
		};
	}
}

extern "C" __declspec(dllexport) Engine::IRenderer* Create();