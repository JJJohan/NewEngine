#pragma once
#include <string>

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include "../Core/Common.h"
#include "ICamera.h"
#include "IRenderer.h"

namespace Engine
{
	class GameObject;

	class RenderSystem
	{
	public:
		ENGINE_API static RenderSystem* Instance();
		
		bool Initialise(const std::string& moduleName);
		IRenderer* Create();

		template <class T>
		T* CreateComponent(GameObject* owner)
		{
			return nullptr;
		}

		template<>
		ICamera* CreateComponent<ICamera>(GameObject* owner)
		{
			if (_pRenderer != nullptr)
			{
				return _pRenderer->CreateCamera(owner);
			}

			return nullptr;
		}

	private:
		RenderSystem();
		~RenderSystem();

		void Shutdown();

		static RenderSystem* _pInstance;
		HMODULE _pHandle;
		IRenderer* _pRenderer;
	};
}
