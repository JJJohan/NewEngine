#pragma once

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include "../Core/IRegisteredClass.h"

namespace Engine
{
	class Window : IRegisteredClass
	{
	public:
		static Window* Initialise(int width, int height, bool windowed);
		static Window* Instance();

		int GetWidth() const;
		int GetHeight() const;
		bool IsFullscreen() const;
		void Shutdown();
		void SetResolution(int width, int height, bool fullscreen);

		HWND Handle;

	private:
		Window(int width, int height, bool windowed);
		~Window();
		void Update();
		void Register() override;
		void RegisterInput();

		static Window* _pInstance;
		int _width;
		int _height;
		bool _fullscreen;
		WINDOWPLACEMENT _wpPrev;
	};
}
