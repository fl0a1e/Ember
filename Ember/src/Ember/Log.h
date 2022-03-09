#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ember {

	class EMBER_API Log{
	public:
		static void Init();	// customized pattern & create logger & set level

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define EMBER_CORE_TRACE(...)	::Ember::Log::getCoreLogger()->trace(__VA_ARGS__)
#define EMBER_CORE_INFO(...)	::Ember::Log::getCoreLogger()->info(__VA_ARGS__)
#define EMBER_CORE_WARN(...)	::Ember::Log::getCoreLogger()->warn(__VA_ARGS__)
#define EMBER_CORE_ERR(...)		::Ember::Log::getCoreLogger()->error(__VA_ARGS__)
#define EMBER_CORE_FATAL(...)	::Ember::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define EMBER_Client_TRACE(...)	::Ember::Log::getClientLogger()->trace(__VA_ARGS__)
#define EMBER_Client_INFO(...)	::Ember::Log::getClientLogger()->info(__VA_ARGS__)
#define EMBER_Client_WARN(...)	::Ember::Log::getClientLogger()->warn(__VA_ARGS__)
#define EMBER_Client_ERR(...)	::Ember::Log::getClientLogger()->error(__VA_ARGS__)
#define EMBER_Client_FATAL(...)	::Ember::Log::getClientLogger()->fatal(__VA_ARGS__)

