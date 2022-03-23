#pragma once

#include "Ember/Layer.h"

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
		float imGUILayer_time = 0.0f;
	};
}