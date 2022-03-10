#pragma once

#include "pch.h"
#include "Ember/Core.h"


namespace Ember {

	// ---------------------
	// don't use buffer now
	// ---------------------

	// -------------------------------------
	// enum��enum class���������Ƿ��޶���������
	// enum������Ⱦ�ⲿ��������
	// -------------------------------------
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	// �¼�����
	// for filtering some specific events
	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),	// 00001
		EventCategoryInput			= BIT(1),	// 00010
		EventCategoryKeyboard		= BIT(2),	// 00100
		EventCategoryMouse			= BIT(3),	// 01000
		EventCategoryMouseButton	= BIT(4),	// 10000
	};

	// ���ú��Զ��������������Ҫ�Ļ�����������
	// -----------------------------------------------------------------------
#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category)	virtual int getEventCategory() const override { return category; }
// --------------------------------------------------------------------------------

	// base class for events
	class EMBER_API Event {
	public:
		bool isHandled = false;	// �Ƿ��ѱ����� & ʹ���²��֪���¼��ķ���

		virtual EventType getEventType() const = 0;
		virtual int getEventCategory() const = 0;
		virtual const char* getName()const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) {
			return getEventCategory() & category;
		}

	};


	// ������
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