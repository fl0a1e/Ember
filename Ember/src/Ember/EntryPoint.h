#pragma once

#ifdef EMBER_PLATFORM_WINDOWS

// only use function of createApp so we use 'extern' rather than '#include'
extern Ember::App* Ember::createApp();

int main(int argc, char** argv) {

	// logger
	Ember::Log::Init();
	EMBER_CORE_WARN("Initialized Ember logger!");
	EMBER_Client_INFO("Initialized Client logger!");

	// loop
	auto app = Ember::createApp();
	app->Run();
	delete app;
}

#endif