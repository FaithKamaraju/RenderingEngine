#pragma once
#include "core.h"

//Forward declarations
struct GLFWwindow;
namespace RE {

	class RE_API Renderer 
	{
	public:
		
		void processInput(GLFWwindow* window);
		int mainLoop();
	};

	RE_API void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
	RE_API Renderer* createRenderer();
	
}
