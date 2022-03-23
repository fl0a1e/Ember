#include "pch.h"
#include "LayerStack.h"


namespace Ember {

	LayerStack::LayerStack() {
		layersInsert = layersVec.begin();
	}

	LayerStack::~LayerStack() {
		for (auto layer : layersVec) {
			delete layer;
		}
	}

	
	void LayerStack::pushLayer(Layer* layer) {
		layersInsert = layersVec.emplace(layersInsert, layer);
	}

	
	void LayerStack::pushOverlay(Layer* overlay) {
		layersVec.emplace_back(overlay);
	}
	
	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(layersVec.begin(), layersVec.end(), layer);
		if ( it!=layersVec.end() ) {
			layersVec.erase(it);
			layersInsert--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		auto it = std::find(layersVec.begin(), layersVec.end(), overlay);
		if ( it != layersVec.end() ) {
			layersVec.erase(it);
		}
	}

}