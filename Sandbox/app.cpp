#include <iostream>
#include "Renderer/renderer.h"

#ifdef RE_PLATFORM_WINDOWS
	#include <Windows.h>
	extern "C" {
		__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;// Optimus: force switch to discrete GPU
		//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;//AMD
	}
#endif

int main() {
	RE::Renderer* renderer = RE::createRenderer();
	if (!renderer) {
		std::cerr << "Failed to create renderer." << std::endl;
		return -1;
	}
	int result = renderer->mainLoop();
	delete renderer;
}