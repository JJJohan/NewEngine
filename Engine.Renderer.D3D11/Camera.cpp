#include "Camera.h"
#include "Utils\Logger.h"

namespace Engine
{
	namespace Renderer
	{
		Camera::Camera(GameObject* owner) : ICamera(owner)
			, _pContext(nullptr)
			, _pRTV(nullptr)
		{
			_pClearColour = new FLOAT[4]{ DefaultClearColour.GetRed(), DefaultClearColour.GetGreen(), DefaultClearColour.GetBlue()};
		}

		Camera::~Camera()
		{
			delete[] _pClearColour;
		}

		void Camera::Render()
		{
			if (_pContext == nullptr)
			{
				Logger::Instance()->LogError("Camera attempted to render without being initialised.");
			}

			_pContext->ClearRenderTargetView(_pRTV, _pClearColour);			
		}

		void Camera::SetClearColour(const Colour& colour)
		{
			_clearColour = colour;
			_pClearColour[0] = colour.GetRed();
			_pClearColour[1] = colour.GetGreen();
			_pClearColour[2] = colour.GetBlue();
			_pClearColour[3] = colour.GetAlpha();
		}

		void Camera::Initialise(ID3D11Device* device, IDXGISwapChain* swapChain, ID3D11DeviceContext* context)
		{
			_pContext = context;

			if (_pRTV != nullptr)
			{
				Logger::Instance()->LogError("Attempted to initialise camera a second time.");
				return;
			}

			//Create our BackBuffer
			ID3D11Texture2D* BackBuffer;
			HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));

			//Create our Render Target
			hr = device->CreateRenderTargetView(BackBuffer, nullptr, &_pRTV);
			BackBuffer->Release();

			//Set our Render Target
			_pContext->OMSetRenderTargets(1, &_pRTV, nullptr);
		}
	}
}