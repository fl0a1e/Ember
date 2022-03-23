#pragma once

#include "pch.h"

#include "Ember/Core.h"
#include "Layer.h"



namespace Ember {

	class EMBER_API LayerStack {
	private:
		std::vector<Layer*> layersVec;
		std::vector<Layer*>::iterator layersInsert;
	public:
		LayerStack();
		~LayerStack();


		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layersVec.begin(); }
		std::vector<Layer*>::iterator end() { return layersVec.end(); }
	
	};

}



