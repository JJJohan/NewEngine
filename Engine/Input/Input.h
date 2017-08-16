#pragma once
#include <map>
#include <vector>
#include <functional>
#include "../Core/Common.h"

namespace Engine
{
	enum KeyState
	{
		KeyDown,
		KeyUp,
		KeyHeld
	};

	enum MouseState
	{
		ButtonDown,
		ButtonUp,
		ButtonHeld
	};

	class Input
	{
	public:
		ENGINE_API void KeyUpEvent(unsigned short keyCode);
		ENGINE_API void KeyDownEvent(unsigned short keyCode);

		ENGINE_API void MouseButtonUpEvent(unsigned short mouseButton);
		ENGINE_API void MouseButtonDownEvent(unsigned short mouseButton);
		ENGINE_API void MouseMoveEvent(long deltaX, long deltaY);

		ENGINE_API void RegisterKey(int keyCode, KeyState keyState, const std::function<void()>& event, std::string eventName);
		ENGINE_API void RegisterMouseButton(int mouseButton, MouseState mouseState, const std::function<void()>& event, std::string eventName);
		ENGINE_API void RegisterMouseMoveEvent(const std::function<void(long x, long y)>& event, std::string eventName);

		ENGINE_API void UnregisterKey(std::string eventName);
		ENGINE_API void UnregisterMouseButton(std::string eventName);
		ENGINE_API void UnregisterMouseMoveEvent(std::string eventName);

		void Update();
		static ENGINE_API Input* Instance();

	private:
		Input();
		
		static void Shutdown();

		bool KeyEventExists(std::string eventName);
		bool MouseEventExists(std::string eventName);
		bool MouseMoveEventExists(std::string eventName);

		void DeleteKey(std::string eventName);
		void DeleteMouseButton(std::string eventName);
		void DeleteMouseMoveEvent(std::string eventName);

		struct KeyEvent
		{
			KeyState KeyState;
			std::function<void()> Event;
			std::string EventName;
		};

		struct MouseEvent
		{
			MouseState MouseState;
			std::function<void()> Event;
			std::string EventName;
		};

		struct MMoveEvent
		{
			std::function<void(long x, long y)> Event;
			std::string EventName;
		};

		enum DeleteType
		{
			Delete_Key,
			Delete_Mouse,
			Delete_MMove
		};

		void CallKeyEvents(int keyCode, bool keyPressed);
		void CallMouseEvents(int mouseButton, bool buttonPressed);
		static Input* _pInstance;

		std::map<int, std::vector<KeyEvent>> _keyEvents;
		std::map<unsigned short, bool> _activeKeys;
		std::map<int, std::vector<MouseEvent>> _mouseEvents;
		std::map<int, bool> _activeMouseButtons;
		std::vector<MMoveEvent> _mouseMoveEvents;
		std::map<DeleteType, std::vector<std::string>> _deleteQueue;
		bool _deletionQueued;
		bool _keyPressed;
		bool _mousePressed;
	};
}
