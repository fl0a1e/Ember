#pragma once

#include "Core.h"
#include "Window.h"
#include "Ember/LayerStack.h"
#include "Ember/Events/Events.h"
#include "Ember/Events/AppEvents.h"


namespace Ember {

	class EMBER_API App {
	public:
		App();
		virtual ~App();

		void Run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

	private:
		bool onWindowClose(WindowClose& e);

		std::unique_ptr<Window> m_Window;
		bool isRunning = true;

		LayerStack layerStack;
	};

	// to be defined by client
	App* createApp();

}


