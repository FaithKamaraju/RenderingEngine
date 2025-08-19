#include <iostream>
#include "EngineCore/Engine.h"

#ifdef FE_PLATFORM_WINDOWS
	#include <Windows.h>
	extern "C" {
		__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;// Optimus: force switch to discrete GPU
		//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;//AMD
	}
#endif

int main() {
	FE::Engine* engineObj = FE::CreateEngineInstance();
	if (!engineObj) {
		std::cerr << "Failed to create renderer." << std::endl;
		return -1;
	}
	int result = engineObj->StartEngineLoop();
	delete engineObj;
}