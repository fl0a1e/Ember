#pragma once

#include "Core.h"
#include "Events/Events.h"
#include "Window.h"
#include "Ember/Events/AppEvents.h"

namespace Ember {

	class EMBER_API App {
	public:
		App();
		virtual ~App();

		void Run();

		void onEvent(Event& e);

		

	private:
		bool onWindowClose(WindowClose& e);

		std::unique_ptr<Window> m_Window;
		bool isRunning = true;
	};

	// to be defined by client
	App* createApp();

}


