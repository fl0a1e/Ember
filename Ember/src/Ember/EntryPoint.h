#pragma once

#ifdef EMBER_PLATFORM_WINDOWS

// only use function of createApp so we use 'extern' rather than '#include'
extern Ember::App* Ember::createApp();

int main(int argc, char** argv) {
	auto app = Ember::createApp();
	app->Run();
	delete app;
}

#endif