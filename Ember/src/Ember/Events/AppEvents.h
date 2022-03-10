#pragma once

#include "Ember/Events/Events.h"

namespace Ember {

	class EMBER_API WindowResize : public Event {
	private:
		unsigned int width, height;
	public:
		WindowResize(unsigned int _width, unsigned int _height)
			: width(_width), height(_height){}

		unsigned int getWidth() const { return width; }
		unsigned int getHeight() const { return height; }

		std::string toString() const override { 
			std::stringstream ss;
			ss << "WindowResize:" << width << "," << height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};



	class EMBER_API WindowClose : public Event {
	public:
		WindowClose() {}	

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};



	class EMBER_API AppTick : public Event {
	public:
		AppTick() = default;	// the compiler will provide a default constructor for this class

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};



	class EMBER_API AppUpdate : public Event {
	public:
		AppUpdate() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};



	class EMBER_API AppRender : public Event {
	public:
		AppRender() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}