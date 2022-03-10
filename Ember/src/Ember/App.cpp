#include "pch.h"
#include "App.h"
#include "Events/AppEvents.h"

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

	void App::onEvent(Event& e) {
		// �¼�������
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(BIND_EVENT_FN(App::onWindowClose));

		// ����¼���Ϣ
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
