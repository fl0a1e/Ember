#pragma once

// dll链接用宏
#ifdef EMBER_PLATFORM_WINDOWS
	#ifdef EMBER_BUILD_DLL
		#define EMBER_API _declspec(dllexport)
	#else
		#define EMBER_API _declspec(dllimport)
	#endif // DEBUG
#else
	#error EMBER_ONLY_FOR_WINDOWS
#endif


#ifdef EMBER_DEBUG
	#define EMBER_ENABLE_ASSERTS
#endif

// 调试用宏, 输出log
#ifdef EMBER_ENABLE_ASSERTS
	#define EMBER_CLIENT_ASSERT(x, ...) {if(!x) {EMBER_CLIENT_ERR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}   // __debugbreak(); would cause a breakpoint in code.
	#define EMBER_CORE_ASSERT(x, ...) {if(!x) {EMBER_CORE_ERR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define EMBER_CLIENT_ASSERT(x, ...)
	#define EMBER_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)