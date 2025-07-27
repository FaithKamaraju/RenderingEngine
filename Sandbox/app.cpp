#include <iostream>
#include "Renderer/renderer.h"



int main() {
	RE::Renderer* renderer = RE::createRenderer();
	if (!renderer) {
		std::cerr << "Failed to create renderer." << std::endl;
		return -1;
	}
	int result = renderer->mainLoop();
	delete renderer;
}