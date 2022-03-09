#pragma once

#include "Core.h"
#include "Events/Events.h"
#include "Window.h"

namespace Ember {

	class EMBER_API App {
	public:
		App();
		virtual ~App();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool isRunning = true;
	};

	// to be defined by client
	App* createApp();

}


