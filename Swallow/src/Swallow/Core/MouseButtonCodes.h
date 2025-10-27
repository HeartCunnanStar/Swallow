#pragma once

namespace Swallow
{
	enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};
	using Mouse = MouseCode;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define SW_MOUSE_BUTTON_0      ::Swallow::Mouse::Button0
#define SW_MOUSE_BUTTON_1      ::Swallow::Mouse::Button1
#define SW_MOUSE_BUTTON_2      ::Swallow::Mouse::Button2
#define SW_MOUSE_BUTTON_3      ::Swallow::Mouse::Button3
#define SW_MOUSE_BUTTON_4      ::Swallow::Mouse::Button4
#define SW_MOUSE_BUTTON_5      ::Swallow::Mouse::Button5
#define SW_MOUSE_BUTTON_6      ::Swallow::Mouse::Button6
#define SW_MOUSE_BUTTON_7      ::Swallow::Mouse::Button7
#define SW_MOUSE_BUTTON_LAST   ::Swallow::Mouse::ButtonLast
#define SW_MOUSE_BUTTON_LEFT   ::Swallow::Mouse::ButtonLeft
#define SW_MOUSE_BUTTON_RIGHT  ::Swallow::Mouse::ButtonRight
#define SW_MOUSE_BUTTON_MIDDLE ::Swallow::Mouse::ButtonMiddle