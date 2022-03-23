#pragma once

#include "Ember/Events/Events.h"

namespace Ember {

	class EMBER_API MouseMoved : public Event {
	private:
		float mouse_X, mouse_Y;
	public:
		MouseMoved(float x, float y)
			: mouse_X(x), mouse_Y(y) {}

		inline float getX() const { return mouse_X; }
		inline float getY() const { return mouse_Y; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseMoved:" << mouse_X << ", " << mouse_Y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class EMBER_API MouseScrolled : public Event {
	private:
		float offset_X, offset_Y;
	public:
		MouseScrolled(float x, float y)
			: offset_X(x), offset_Y(y) {}

		inline float getOffsetX() const { return offset_X; }
		inline float getOffsetY() const { return offset_Y; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseScrolled:" << getOffsetX() << ", " << getOffsetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class EMBER_API MouseButton : public Event {
	public:
		inline int getMouseButton() const { return mouseCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButton(int button) 
			: mouseCode(button) {}

		int mouseCode;
	};

	class EMBER_API MouseButtonPressed : public MouseButton {
	public:
		MouseButtonPressed(int button)
			: MouseButton(button) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseButtonPressed:" << mouseCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class EMBER_API MouseButtonReleased : public MouseButton {
	public:
		MouseButtonReleased(int button)
			: MouseButton(button) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseButtonReleased:" << mouseCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
