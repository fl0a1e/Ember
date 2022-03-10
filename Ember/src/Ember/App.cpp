#include "pch.h"
#include "App.h"
#include "Events/AppEvents.h"

namespace Ember {

	
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	App::App() {
		m_Window = std::unique_ptr<Window>(Window::Create());

		// 设置窗口回调函数，glfwSet...Callback 事件发生则调用 data.
		// 由 SetEventCallback 设置为 onEvent()
		// onEvent() 通过std::bind 绑定到占位符的参数，即Event& e上
		// 从而根据不同事件调用 事件调度器 EventDispatcher 分配具体函数
		// 先聚合再分配，好像多路复用，多路分解
		m_Window->SetEventCallback(BIND_EVENT_FN(App::onEvent));	
	}

	App::~App() {
	}

	void App::onEvent(Event& e) {
		// 事件调度器
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(BIND_EVENT_FN(App::onWindowClose));

		// 输出事件消息
		EMBER_CORE_TRACE("{0}", e);
	}

	void App::Run() {

		// main loop
		while (isRunning) {

			m_Window->OnUpdate();


		}
	}


	bool App::onWindowClose(WindowClose& e) {
		isRunning = false;
		return true;
	}

}
