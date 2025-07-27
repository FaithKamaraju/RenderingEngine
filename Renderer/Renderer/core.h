#pragma once

#ifdef RE_PLATFORM_WINDOWS
	#include <Windows.h>
	extern "C" {
		__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;// Optimus: force switch to discrete GPU
		//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;//AMD
	}
	#ifdef RE_BUILD_DLL
		#define RE_API __declspec(dllexport)
	#else
		#define RE_API __declspec(dllimport)
	#endif
#else
	#error Rendering Engine only supports Windows!
#endif