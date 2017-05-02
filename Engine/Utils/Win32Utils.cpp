#include "Win32Utils.h"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

namespace Engine
{
	int Win32Utils::ShowMessageBox(const std::string& message, const std::string& title, MessageBoxType messageType)
	{
		HWND handle = nullptr;
		//HWND handle = Renderer::GetWindowHandle();
		std::wstring messageW = std::wstring(message.begin(), message.end());
		std::wstring titleW = std::wstring(title.begin(), title.end());
		return MessageBoxEx(handle, messageW.c_str(), titleW.c_str(), 0, 0);
	}
}
