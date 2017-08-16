#pragma once
#include "../Core/Common.h"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <string>
#include "../Core/IRegisteredClass.h"

namespace Engine
{
	class String;
	class Vector2;
	class Colour;

	class Console : IRegisteredClass
	{
	public:
		enum ConsoleColour
		{
			Current = -1,
			Black = 0,
			DarkBlue = 1,
			DarkGreen = 2,
			DarkAqua,
			DarkCyan = 3,
			DarkRed = 4,
			DarkPurple = 5,
			DarkPink = 5,
			DarkMagenta = 5,
			DarkYellow = 6,
			DarkWhite = 7,
			Gray = 8,
			Blue = 9,
			Green = 10,
			Aqua = 11,
			Cyan = 11,
			Red = 12,
			Purple = 13,
			Pink = 13,
			Magenta = 13,
			Yellow = 14,
			White = 15
		};

		ENGINE_API void InitConsole();
		ENGINE_API void SetColour(ConsoleColour textColour, ConsoleColour backgroundColour = Current);
		ENGINE_API ConsoleColour GetTextColour();
		ENGINE_API ConsoleColour GetBackgroundColour();
		ENGINE_API Vector2 GetCursorPos();
		ENGINE_API void SetCursorPos(int x, int y);
		ENGINE_API void SetTitle(const std::string& title);

		void Register() override;

		static ENGINE_API Console* Instance();

	private:
		Console();
		static void Shutdown();

		static Console* _pInstance;

		static bool HandlerRoutine(DWORD ctrlType);
		static short _textColour;
		static short _backgroundColour;
	};
}
