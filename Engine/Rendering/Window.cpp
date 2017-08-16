#include "Window.h"
#include "../Core/Core.h"
#include "../Core/Lua.h"
#include "../Input/Input.h"

namespace Engine
{
	Window* Window::_pInstance = nullptr;

	Window* Window::Instance()
	{
		return _pInstance;
	}

	Window* Window::Initialise(int width, int height, bool fullscreen)
	{
		if (_pInstance == nullptr)
		{
			_pInstance = new Window(width, height, fullscreen);
		}

		return _pInstance;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* instance = Window::Instance();

		switch (msg)
		{
		case WM_CLOSE:
			if (instance != nullptr && instance->Handle == hwnd)
			{
				instance->Shutdown();
			}

			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			Core::Instance()->Shutdown();
			break;

		case WM_INPUT:
		{
			UINT dwSize;

			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dwSize,
				sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			if (lpb == nullptr)
			{
				return 0;
			}

			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize,
				sizeof(RAWINPUTHEADER)) != dwSize)
				OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				/*raw->data.keyboard.MakeCode
				raw->data.keyboard.Flags
				raw->data.keyboard.Reserved
				raw->data.keyboard.ExtraInformation
				raw->data.keyboard.Message
				raw->data.keyboard.VKey*/
				
				RAWKEYBOARD keyboard = raw->data.keyboard;
				if (keyboard.Flags == RI_KEY_BREAK)
				{

					Input::Instance()->KeyUpEvent(keyboard.VKey);
				}
				else if (keyboard.Flags == RI_KEY_MAKE)
				{
					Input::Instance()->KeyDownEvent(keyboard.VKey);
				}
			}
			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{
				/*raw->data.mouse.usFlags
				raw->data.mouse.ulButtons
				raw->data.mouse.usButtonFlags
				raw->data.mouse.usButtonData
				raw->data.mouse.ulRawButtons
				raw->data.mouse.lLastX
				raw->data.mouse.lLastY
				raw->data.mouse.ulExtraInformation*/

				RAWMOUSE mouse = raw->data.mouse;
				if (mouse.usFlags == MOUSE_MOVE_ABSOLUTE)
				{
					Input::Instance()->MouseMoveEvent(mouse.lLastX, mouse.lLastY);
				}
				else if (mouse.usFlags == MOUSE_ATTRIBUTES_CHANGED)
				{
					switch (mouse.usButtonFlags)
					{
					case RI_MOUSE_LEFT_BUTTON_DOWN:
						Input::Instance()->MouseButtonDownEvent(0);
						break;
					case RI_MOUSE_LEFT_BUTTON_UP:
						Input::Instance()->MouseButtonUpEvent(0);

						break;
					case RI_MOUSE_RIGHT_BUTTON_DOWN:
						Input::Instance()->MouseButtonDownEvent(1);
						break;
					case RI_MOUSE_RIGHT_BUTTON_UP:
						Input::Instance()->MouseButtonUpEvent(1);
						break;
					}
				}
			}

			delete[] lpb;
		}

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	void Window::RegisterInput()
	{
		RAWINPUTDEVICE Rid[2];

		Rid[0].usUsagePage = 0x01;
		Rid[0].usUsage = 0x02;
		Rid[0].dwFlags = 0;   // adds HID mouse and also ignores legacy mouse messages
		Rid[0].hwndTarget = nullptr;

		Rid[1].usUsagePage = 0x01;
		Rid[1].usUsage = 0x06;
		Rid[1].dwFlags = 0;   // adds HID keyboard and also ignores legacy keyboard messages
		Rid[1].hwndTarget = nullptr;

		if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) 
		{
			//registration failed. Call GetLastError for the cause of the error
		}
	}

	void Window::SetResolution(int width, int height, bool fullscreen)
	{
		_width = width;
		_height = height;
		_fullscreen = fullscreen;

		DWORD dwStyle = GetWindowLong(Handle, GWL_STYLE);
		if (_fullscreen) 
		{
			MONITORINFO mi = { sizeof(mi) };
			if (GetWindowPlacement(Handle, &_wpPrev) &&	GetMonitorInfo(MonitorFromWindow(Handle, MONITOR_DEFAULTTOPRIMARY), &mi)) 
			{
				SetWindowLong(Handle, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(Handle, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left,	mi.rcMonitor.bottom - mi.rcMonitor.top,	SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
		}
		else 
		{
			SetWindowLong(Handle, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
			SetWindowPlacement(Handle, &_wpPrev);
			SetWindowPos(Handle, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}

	void Window::Register()
	{
		Lua::Instance()->RegisterMethod("Window", "SetResolution", SmartBind(*this, &Window::SetResolution));
	}

	Window::Window(int width, int height, bool fullscreen)
	: Handle(nullptr)
	, _width(width)
	, _height(height)
	, _fullscreen(fullscreen)
	{
		HINSTANCE hInstance = GetModuleHandle(nullptr);

		Core::Instance()->Register(this);
		
		Core::Instance()->OnUpdate += std::bind(&Window::Update, this);
		Core::Instance()->OnShutdown += std::bind(&Window::Shutdown, this);
		
		// Register the Window Class
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = L"EngineWindow";
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(nullptr, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			return;
		}

		// Create the Window
		Handle = CreateWindowEx(WS_EX_CLIENTEDGE, L"EngineWindow", L"Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height,	nullptr, nullptr, hInstance, nullptr);

		if (Handle == nullptr)
		{
			MessageBox(nullptr, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			return;
		}

		RegisterInput();
		SetResolution(width, height, fullscreen);

		ShowWindow(Handle, SW_SHOW);
		UpdateWindow(Handle);
	}

	void Window::Update()
	{
		const int messageLimit = 10;
		int ticks = 0;

		MSG Msg;
		while (GetMessage(&Msg, nullptr, 0, 0) > 0 && ticks < messageLimit)
		{			
			++ticks;
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	void Window::Shutdown()
	{
		if (Handle != nullptr)
		{
			PostQuitMessage(0);
			Handle = nullptr;
		}

		delete _pInstance;
	}

	Window::~Window()
	{
		_pInstance = nullptr;
	}

	int Window::GetWidth() const
	{
		return _width;
	}

	int Window::GetHeight() const
	{
		return _height;
	}

	bool Window::IsFullscreen() const
	{
		return _fullscreen;
	}

}
