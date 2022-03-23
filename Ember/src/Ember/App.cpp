#include "pch.h"
#include "Ember/App.h"
#include "Events/AppEvents.h"
#include "Ember/LayerStack.h"


#include "glad/glad.h"

namespace Ember {
	
	App* App::s_Instance = nullptr;

	App::App() {
		EMBER_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

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

	void App::pushLayer(Layer* layer) {
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void App::pushOverlay(Layer* overlay) {
		layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void App::onEvent(Event& e) {
		// 事件调度器
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(BIND_EVENT_FN(App::onWindowClose));

		// 输出事件消息
		EMBER_CORE_TRACE("{0}", e);

		// 自上而下传递事件消息
		for (auto it = layerStack.end(); it != layerStack.begin(); ) {
			(*--it)->onEvent(e);
			if (e.isHandled) {
				break;
			}
		}
	}

	void App::Run() {

		// main loop
		while (isRunning) {
			
			// 刷新窗口，防止内部窗口拖尾
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// 更新每层 layer
			for (Layer* layer : layerStack) {
				layer->onUpdate();
			}

			
			m_Window->OnUpdate();


		}
	}


	bool App::onWindowClose(WindowClose& e) {
		isRunning = false;
		return true;
	}

}
