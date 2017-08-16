#include "RenderSystem.h"
#include "../Core/Core.h"
#include "../Utils/Logger.h"

namespace Engine
{
	RenderSystem* RenderSystem::_pInstance = nullptr;
	
	RenderSystem::RenderSystem()
		: _pRenderer(nullptr)
	{
		Core::Instance()->OnShutdown += std::bind(&RenderSystem::Shutdown, this);
	}

	void RenderSystem::Shutdown()
	{
		if (_pRenderer != nullptr)
		{
			delete _pRenderer;
			_pRenderer = nullptr;
		}

		if (_pHandle != nullptr)
		{
			FreeLibrary(_pHandle);
			_pHandle = nullptr;
		}
		delete _pInstance;
	}

	RenderSystem::~RenderSystem()
	{
		_pInstance = nullptr;
	}

	RenderSystem* RenderSystem::Instance()
	{
		if (_pInstance == nullptr)
		{
			_pInstance = new RenderSystem();
		}

		return _pInstance;
	}


	IRenderer* RenderSystem::Create()
	{
		if (_pHandle != nullptr)
		{
			const auto func = reinterpret_cast<IRenderer*(*)()>(GetProcAddress(_pHandle, "Create"));
			if (func != nullptr)
			{
				_pRenderer = func();
				return _pRenderer;
			}
		}

		return nullptr;
	}

	bool RenderSystem::Initialise(const std::string& name)
	{
		const std::wstring str = std::wstring(name.begin(), name.end());
		_pHandle = LoadLibrary((L"Engine.Renderer." + str + L".dll").c_str());
		if (_pHandle != nullptr)
		{
			Logger::Instance()->Log("Renderer '{0}' initialised.", name);
			return true;
		}

		Logger::Instance()->LogWarning("Renderer '{0}' unavailable.", name);
		return false;
	}
}
