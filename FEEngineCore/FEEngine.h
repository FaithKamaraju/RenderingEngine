#pragma once


#ifdef FE_PLATFORM_WINDOWS
	#include <Windows.h>
	extern "C" {
		__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;// Optimus: force switch to discrete GPU
		//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;//AMD
	}
	#include "EngineMacros.h"
	#include "EntryPoint.h"

#else
	#error FE Engine only supports Windows!
#endif

