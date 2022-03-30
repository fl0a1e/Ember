#include "pch.h"
#include "LayerStack.h"


namespace Ember {

	LayerStack::LayerStack() {
		
	}

	LayerStack::~LayerStack() {
		for (auto layer : layersVec) {
			delete layer;
		}
	}

	
	void LayerStack::pushLayer(Layer* layer) {
		layersVec.emplace(layersVec.begin() + layersInsertIndex, layer);
		layersInsertIndex++;
	}

	
	void LayerStack::pushOverlay(Layer* overlay) {
		layersVec.emplace_back(overlay);
	}
	
	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(layersVec.begin(), layersVec.end(), layer);
		if ( it!=layersVec.end() ) {
			layersVec.erase(it);
			layersInsertIndex--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		auto it = std::find(layersVec.begin(), layersVec.end(), overlay);
		if ( it != layersVec.end() ) {
			layersVec.erase(it);
		}
	}

}