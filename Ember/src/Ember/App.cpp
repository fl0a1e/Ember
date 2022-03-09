#include "pch.h"
#include "App.h"
#include "Events/AppEvents.h"
#include "Window.h"

namespace Ember {

	App::App() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	App::~App() {
	}

	void App::Run() {
		WindowResize e(1280, 720);
		EMBER_Client_TRACE(e);


		// main loop
		while (isRunning) {

			m_Window->OnUpdate();


		}
	}

}
