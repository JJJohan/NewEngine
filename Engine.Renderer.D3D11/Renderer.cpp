#include "Renderer.h"
#include "Camera.h"
#include "../Engine/Utils/Console.h"
#include "../Engine/Utils/Logger.h"
#include "../Engine/Core/Core.h"

namespace Engine
{
	namespace Renderer
	{
		D3D11::D3D11()
		: _pSwapChain(nullptr)
		, _pDevice(nullptr)
		, _pContext(nullptr)
		{
		}

		D3D11::~D3D11()
		{
			if (_pSwapChain != nullptr)
			{
				_pSwapChain->Release();
				_pSwapChain = nullptr;
			}
			if (_pSwapChain != nullptr)
			{
				_pDevice->Release();
				_pDevice = nullptr;
			}
			if (_pContext != nullptr)
			{
				_pContext->Release();
				_pContext = nullptr;
			}
		}

		void D3D11::Initialise(int width, int height, bool fullscreen, HWND handle)
		{
			Width = width;
			Height = height;
			Handle = handle;
			Fullscreen = fullscreen;

			//Describe our Buffer
			DXGI_MODE_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
			bufferDesc.Width = Width;
			bufferDesc.Height = Height;
			bufferDesc.RefreshRate.Numerator = 60;
			bufferDesc.RefreshRate.Denominator = 1;
			bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			//Describe our SwapChain
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
			swapChainDesc.BufferDesc = bufferDesc;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 1;
			swapChainDesc.OutputWindow = Handle;
			swapChainDesc.Windowed = !Fullscreen;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			//Create our SwapChain
			HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &_pSwapChain, &_pDevice, nullptr, &_pContext);
		}

		void D3D11::Draw()
		{
			Core::Instance()->OnRender.Call();

			size_t cameraCount = Cameras.size();
			for (size_t i = 0; i < cameraCount; ++i)
			{
				Camera* camera = static_cast<Camera*>(Cameras[i]);
				if (camera->Enabled)
				{
					camera->Render();
				}
			}

			_pSwapChain->Present(0, 0);
		}

		ICamera* D3D11::CreateCamera(GameObject* owner)
		{
			Camera* camera = new Camera(owner);
			camera->Initialise(_pDevice, _pSwapChain, _pContext);
			Cameras.push_back(camera);
			return camera;
		}
	}
}

extern "C" Engine::IRenderer* Create()
{
	return new Engine::Renderer::D3D11();
}
