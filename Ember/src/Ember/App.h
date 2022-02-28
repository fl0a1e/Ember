#pragma once

#include "Core.h"

namespace Ember {

	class EMBER_API App {
	public:
		App();
		virtual ~App();

		void Run();
	};

	// 
	App* createApp();

}


