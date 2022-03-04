#pragma once

#include "Core.h"

namespace Ember {

	class EMBER_API App {
	public:
		App();
		virtual ~App();

		void Run();
	};

	// to be defined by client
	App* createApp();

}


