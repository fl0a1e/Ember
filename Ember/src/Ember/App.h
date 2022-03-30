#pragma once

#include "Core.h"
#include "Window.h"
#include "Ember/LayerStack.h"
#include "Ember/Events/Events.h"
#include "Ember/Events/AppEvents.h"

#include "Ember/ImGUI/ImGUILayer.h"

namespace Ember {

	class EMBER_API App {
	public:
		App();
		virtual ~App();

		void Run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static App& get() { return *s_Instance; }

		inline Window& getWindow() { return *m_Window; }
	private:
		bool onWindowClose(WindowClose& e);

		std::unique_ptr<Window> m_Window;
		ImGUILayer* m_imGuiLayer;
		bool isRunning = true;

		LayerStack layerStack;
	private:
		static App* s_Instance;
	};

	// to be defined by client
	App* createApp();

}


