#include "pch.h"
#include "Ember/App.h"
#include "Events/AppEvents.h"
#include "Ember/LayerStack.h"


#include "glad/glad.h"

namespace Ember {

	
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	App::App() {
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
	}

	void App::pushOverlay(Layer* overlay) {
		layerStack.pushOverlay(overlay);
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
