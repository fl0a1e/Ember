#pragma once


#ifdef EMBER_PLATFORM_WINDOWS
	#ifdef EMBER_BUILD_DLL
		#define EMBER_API _declspec(dllexport)
	#else
		#define EMBER_API _declspec(dllimport)
	#endif // DEBUG
#else
	#error EMBER_ONLY_FOR_WINDOWS
#endif