#include "Ember.h"

class boxLayer : public Ember::Layer {
public:
	boxLayer() 
		: Layer("BoxLayer"){}

	void onUpdate() override {
		EMBER_Client_INFO("BoxLayer::onUpdate.");
	}

	void onEvent(Ember::Event& e) override {
		EMBER_Client_TRACE("{0}" , e);
	}

};


class SandBox : public Ember::App {
public:
	SandBox() {
		pushLayer(new boxLayer());
		pushOverlay(new Ember::ImGUILayer());
	}

	~SandBox() {

	}
};


Ember::App* Ember::createApp() {
	return new SandBox();
}