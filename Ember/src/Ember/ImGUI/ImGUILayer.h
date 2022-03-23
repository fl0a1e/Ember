#pragma once

#include "Ember/Layer.h"
#include "Ember/Events/AppEvents.h"
#include "Ember/Events/KeyEvents.h"
#include "Ember/Events/MouseEvents.h"

namespace Ember {

	class EMBER_API ImGUILayer : public Layer {
	public:
		ImGUILayer();
		~ImGUILayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	private:
		bool onMouseButtonPressed(MouseButtonPressed& e);
		bool onMouseButtonReleased(MouseButtonReleased& e);
		bool onMouseScrolled(MouseScrolled& e);
		bool onMouseMoved(MouseMoved& e);
		bool onKeyPressed(KeyPressed& e);
		bool onKeyReleased(KeyReleased& e);
		//bool onKeyTyped(KeyTyped& e);
		bool onWindowResize(WindowResize& e);

	private:
		float imGUILayer_time = 0.0f;
	};
}