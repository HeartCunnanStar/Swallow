#pragma once

#include "Event.h"

namespace Swallow {

	class SWALLOW_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_key_code(keycode) {
		}

		int m_key_code;
	};

	class SWALLOW_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeated_count)
			: KeyEvent(keycode), m_repeated_count(repeated_count) {
		}

		inline int GetRepeatCount() const { return m_repeated_count; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_key_code << " (" << m_repeated_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeated_count;
	};

	class SWALLOW_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}