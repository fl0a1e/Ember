#include "Ember.h"


class SandBox : public Ember::App {
public:
	SandBox() {
		pushOverlay(new Ember::ImGUILayer());
	}

	~SandBox() {

	}
};


Ember::App* Ember::createApp() {
	return new SandBox();
}