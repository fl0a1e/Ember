#pragma once

#include "Ember/Events/Events.h"

namespace Ember {

	// base class for key events
	// -----------------------------------------------------------------
	class EMBER_API KeyEvent : public Event {
	protected:
		int keyCode;
		KeyEvent(int _keyCode) : keyCode(_keyCode) {}
	public:
		inline int getKeyCode() const { return keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};
	// ------------------------------------------------------------------


	// KeyPressed
	class EMBER_API KeyPressed : public KeyEvent {
	private:
		int repeatCount;
	public:
		KeyPressed(int _keycode, int _repeatCount)
			: KeyEvent(_keycode), repeatCount(_repeatCount) {}

		inline int getRepeatCount() const { return repeatCount; }

		std::string toString() const override { 
			std::stringstream ss;
			ss << "KeyPressed:" << keyCode << "(" << repeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};


	// KeyReleased
	class EMBER_API KeyReleased : public KeyEvent {
	public:
		KeyReleased(int _keyCode)
			: KeyEvent(_keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleased: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class EMBER_API KeyTyped : public KeyEvent {
	public:
		KeyTyped(int _keyCode)
			: KeyEvent(_keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyTyped:" << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}