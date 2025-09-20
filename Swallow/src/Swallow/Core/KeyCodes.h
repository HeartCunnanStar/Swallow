#pragma once

namespace Swallow
{
	enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39,	/* ' */
		Comma = 44,			/* , */
		Minus = 45,			/* - */
		Period = 46,		/* . */
		Slash = 47,			/* / */

		D0 = 48,			/* 0 */
		D1 = 49,			/* 1 */
		D2 = 50,			/* 2 */
		D3 = 51,			/* 3 */
		D4 = 52,			/* 4 */
		D5 = 53,			/* 5 */
		D6 = 54,			/* 6 */
		D7 = 55,			/* 7 */
		D8 = 56,			/* 8 */
		D9 = 57,			/* 9 */

		Semicolon = 59,		/* ; */
		Equal = 61,			/* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,	/* [ */
		Backslash = 92,		/* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,	/* ` */

		World1 = 161,		/* non-US #1 */
		World2 = 162,		/* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};
	using Key = KeyCode;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define SW_KEY_SPACE           ::Swallow::Key::Space
#define SW_KEY_APOSTROPHE      ::Swallow::Key::Apostrophe    /* ' */
#define SW_KEY_COMMA           ::Swallow::Key::Comma         /* , */
#define SW_KEY_MINUS           ::Swallow::Key::Minus         /* - */
#define SW_KEY_PERIOD          ::Swallow::Key::Period        /* . */
#define SW_KEY_SLASH           ::Swallow::Key::Slash         /* / */
#define SW_KEY_0               ::Swallow::Key::D0
#define SW_KEY_1               ::Swallow::Key::D1
#define SW_KEY_2               ::Swallow::Key::D2
#define SW_KEY_3               ::Swallow::Key::D3
#define SW_KEY_4               ::Swallow::Key::D4
#define SW_KEY_5               ::Swallow::Key::D5
#define SW_KEY_6               ::Swallow::Key::D6
#define SW_KEY_7               ::Swallow::Key::D7
#define SW_KEY_8               ::Swallow::Key::D8
#define SW_KEY_9               ::Swallow::Key::D9
#define SW_KEY_SEMICOLON       ::Swallow::Key::Semicolon     /* ; */
#define SW_KEY_EQUAL           ::Swallow::Key::Equal         /* = */
#define SW_KEY_A               ::Swallow::Key::A
#define SW_KEY_B               ::Swallow::Key::B
#define SW_KEY_C               ::Swallow::Key::C
#define SW_KEY_D               ::Swallow::Key::D
#define SW_KEY_E               ::Swallow::Key::E
#define SW_KEY_F               ::Swallow::Key::F
#define SW_KEY_G               ::Swallow::Key::G
#define SW_KEY_H               ::Swallow::Key::H
#define SW_KEY_I               ::Swallow::Key::I
#define SW_KEY_J               ::Swallow::Key::J
#define SW_KEY_K               ::Swallow::Key::K
#define SW_KEY_L               ::Swallow::Key::L
#define SW_KEY_M               ::Swallow::Key::M
#define SW_KEY_N               ::Swallow::Key::N
#define SW_KEY_O               ::Swallow::Key::O
#define SW_KEY_P               ::Swallow::Key::P
#define SW_KEY_Q               ::Swallow::Key::Q
#define SW_KEY_R               ::Swallow::Key::R
#define SW_KEY_S               ::Swallow::Key::S
#define SW_KEY_T               ::Swallow::Key::T
#define SW_KEY_U               ::Swallow::Key::U
#define SW_KEY_V               ::Swallow::Key::V
#define SW_KEY_W               ::Swallow::Key::W
#define SW_KEY_X               ::Swallow::Key::X
#define SW_KEY_Y               ::Swallow::Key::Y
#define SW_KEY_Z               ::Swallow::Key::Z
#define SW_KEY_LEFT_BRACKET    ::Swallow::Key::LeftBracket   /* [ */
#define SW_KEY_BACKSLASH       ::Swallow::Key::Backslash     /* \ */
#define SW_KEY_RIGHT_BRACKET   ::Swallow::Key::RightBracket  /* ] */
#define SW_KEY_GRAVE_ACCENT    ::Swallow::Key::GraveAccent   /* ` */
#define SW_KEY_WORLD_1         ::Swallow::Key::World1        /* non-US #1 */
#define SW_KEY_WORLD_2         ::Swallow::Key::World2        /* non-US #2 */

/* Function keys */
#define SW_KEY_ESCAPE          ::Swallow::Key::Escape
#define SW_KEY_ENTER           ::Swallow::Key::Enter
#define SW_KEY_TAB             ::Swallow::Key::Tab
#define SW_KEY_BACKSPACE       ::Swallow::Key::Backspace
#define SW_KEY_INSERT          ::Swallow::Key::Insert
#define SW_KEY_DELETE          ::Swallow::Key::Delete
#define SW_KEY_RIGHT           ::Swallow::Key::Right
#define SW_KEY_LEFT            ::Swallow::Key::Left
#define SW_KEY_DOWN            ::Swallow::Key::Down
#define SW_KEY_UP              ::Swallow::Key::Up
#define SW_KEY_PAGE_UP         ::Swallow::Key::PageUp
#define SW_KEY_PAGE_DOWN       ::Swallow::Key::PageDown
#define SW_KEY_HOME            ::Swallow::Key::Home
#define SW_KEY_END             ::Swallow::Key::End
#define SW_KEY_CAPS_LOCK       ::Swallow::Key::CapsLock
#define SW_KEY_SCROLL_LOCK     ::Swallow::Key::ScrollLock
#define SW_KEY_NUM_LOCK        ::Swallow::Key::NumLock
#define SW_KEY_PRINT_SCREEN    ::Swallow::Key::PrintScreen
#define SW_KEY_PAUSE           ::Swallow::Key::Pause
#define SW_KEY_F1              ::Swallow::Key::F1
#define SW_KEY_F2              ::Swallow::Key::F2
#define SW_KEY_F3              ::Swallow::Key::F3
#define SW_KEY_F4              ::Swallow::Key::F4
#define SW_KEY_F5              ::Swallow::Key::F5
#define SW_KEY_F6              ::Swallow::Key::F6
#define SW_KEY_F7              ::Swallow::Key::F7
#define SW_KEY_F8              ::Swallow::Key::F8
#define SW_KEY_F9              ::Swallow::Key::F9
#define SW_KEY_F10             ::Swallow::Key::F10
#define SW_KEY_F11             ::Swallow::Key::F11
#define SW_KEY_F12             ::Swallow::Key::F12
#define SW_KEY_F13             ::Swallow::Key::F13
#define SW_KEY_F14             ::Swallow::Key::F14
#define SW_KEY_F15             ::Swallow::Key::F15
#define SW_KEY_F16             ::Swallow::Key::F16
#define SW_KEY_F17             ::Swallow::Key::F17
#define SW_KEY_F18             ::Swallow::Key::F18
#define SW_KEY_F19             ::Swallow::Key::F19
#define SW_KEY_F20             ::Swallow::Key::F20
#define SW_KEY_F21             ::Swallow::Key::F21
#define SW_KEY_F22             ::Swallow::Key::F22
#define SW_KEY_F23             ::Swallow::Key::F23
#define SW_KEY_F24             ::Swallow::Key::F24
#define SW_KEY_F25             ::Swallow::Key::F25

/* Keypad */
#define SW_KEY_KP_0            ::Swallow::Key::KP0
#define SW_KEY_KP_1            ::Swallow::Key::KP1
#define SW_KEY_KP_2            ::Swallow::Key::KP2
#define SW_KEY_KP_3            ::Swallow::Key::KP3
#define SW_KEY_KP_4            ::Swallow::Key::KP4
#define SW_KEY_KP_5            ::Swallow::Key::KP5
#define SW_KEY_KP_6            ::Swallow::Key::KP6
#define SW_KEY_KP_7            ::Swallow::Key::KP7
#define SW_KEY_KP_8            ::Swallow::Key::KP8
#define SW_KEY_KP_9            ::Swallow::Key::KP9
#define SW_KEY_KP_DECIMAL      ::Swallow::Key::KPDecimal
#define SW_KEY_KP_DIVIDE       ::Swallow::Key::KPDivide
#define SW_KEY_KP_MULTIPLY     ::Swallow::Key::KPMultiply
#define SW_KEY_KP_SUBTRACT     ::Swallow::Key::KPSubtract
#define SW_KEY_KP_ADD          ::Swallow::Key::KPAdd
#define SW_KEY_KP_ENTER        ::Swallow::Key::KPEnter
#define SW_KEY_KP_EQUAL        ::Swallow::Key::KPEqual

#define SW_KEY_LEFT_SHIFT      ::Swallow::Key::LeftShift
#define SW_KEY_LEFT_CONTROL    ::Swallow::Key::LeftControl
#define SW_KEY_LEFT_ALT        ::Swallow::Key::LeftAlt
#define SW_KEY_LEFT_SUPER      ::Swallow::Key::LeftSuper
#define SW_KEY_RIGHT_SHIFT     ::Swallow::Key::RightShift
#define SW_KEY_RIGHT_CONTROL   ::Swallow::Key::RightControl
#define SW_KEY_RIGHT_ALT       ::Swallow::Key::RightAlt
#define SW_KEY_RIGHT_SUPER     ::Swallow::Key::RightSuper
#define SW_KEY_MENU            ::Swallow::Key::Menu