#pragma once

#include "Renderer/OpenGL/ErrorChecking.h"

#ifdef FE_PLATFORM_WINDOWS
	//#include <Windows.h>
	//extern "C" {
	//	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;// Optimus: force switch to discrete GPU
	//	//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;//AMD
	//}
	
	#ifdef FE_BUILD_DLL
		#define FE_API __declspec(dllexport)
	#elif (defined FE_DLL)
		#define FE_API __declspec(dllimport)
	#endif
#else
	#error FE Engine only supports Windows!
#endif

#pragma warning( disable: 4251 )
