#include "pch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ember {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	
	void Log::Init() {
		spdlog::set_pattern("%^[%H:%M:%S]-[%n]: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Ember");
		s_CoreLogger->set_level(spdlog::level::trace); // trace level will print all massages

		s_ClientLogger = spdlog::stdout_color_mt("Client");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
