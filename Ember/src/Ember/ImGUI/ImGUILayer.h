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

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void Begin();
		void End();
	private:
		float imGUILayer_time = 0.0f;
	};
}