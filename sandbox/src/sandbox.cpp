#include "Ember.h"

class SandBox : public Ember::App {
public:
	SandBox() {

	}

	~SandBox() {

	}
};


Ember::App* Ember::createApp() {
	return new SandBox();
}