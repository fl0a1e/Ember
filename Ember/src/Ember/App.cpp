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

		// ���ô��ڻص�������glfwSet...Callback �¼���������� data.
		// �� SetEventCallback ����Ϊ onEvent()
		// onEvent() ͨ��std::bind �󶨵�ռλ���Ĳ�������Event& e��
		// �Ӷ����ݲ�ͬ�¼����� �¼������� EventDispatcher ������庯��
		// �Ⱦۺ��ٷ��䣬�����·���ã���·�ֽ�
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
		// �¼�������
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(BIND_EVENT_FN(App::onWindowClose));

		// ����¼���Ϣ
		EMBER_CORE_TRACE("{0}", e);

		// ���϶��´����¼���Ϣ
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
			
			// ˢ�´��ڣ���ֹ�ڲ�������β
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// ����ÿ�� layer
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
