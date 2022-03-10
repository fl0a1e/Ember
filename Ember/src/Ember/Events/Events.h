#pragma once

#include "pch.h"
#include "Ember/Core.h"


namespace Ember {

	// ---------------------
	// don't use buffer now
	// ---------------------

	// -------------------------------------
	// enum与enum class区别在于是否限定其作用域
	// enum可能污染外部的作用域
	// -------------------------------------
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	// 事件分类
	// for filtering some specific events
	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),	// 00001
		EventCategoryInput			= BIT(1),	// 00010
		EventCategoryKeyboard		= BIT(2),	// 00100
		EventCategoryMouse			= BIT(3),	// 01000
		EventCategoryMouseButton	= BIT(4),	// 10000
	};

	// 利用宏自动填充派生类中需要的基本函数定义
	// -----------------------------------------------------------------------
#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category)	virtual int getEventCategory() const override { return category; }
// --------------------------------------------------------------------------------

	// base class for events
	class EMBER_API Event {
	public:
		bool isHandled = false;	// 是否已被处理 & 使更下层感知到事件的发生

		virtual EventType getEventType() const = 0;
		virtual int getEventCategory() const = 0;
		virtual const char* getName()const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) {
			return getEventCategory() & category;
		}

	};


	// 调度器
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	private:
		Event& event;
	public:
		EventDispatcher(Event& _event)
			: event(_event) {}


		template<typename T>
		bool dispatch(EventFn<T> func)
		{
			if (event.getEventType() == T::getStaticType())
			{
				event.isHandled = func(*(T*) & (event));
				return true;
			}
			return false;
		}

	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.toString();
	}


}