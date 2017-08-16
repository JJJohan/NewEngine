#pragma once

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windows.h>
#include <vector>

namespace Engine
{
	class ICamera;
	class IScene;
	class IMesh;
	class GameObject;

	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;
		virtual void Initialise(int width, int height, bool fullscreen, HWND handle) = 0;
		virtual void Draw() = 0;

		virtual ICamera* CreateCamera(GameObject* owner) = 0;

	protected:
		int Width;
		int Height;
		bool Fullscreen;
		HWND Handle;
		std::vector<ICamera*> Cameras;
	};
}