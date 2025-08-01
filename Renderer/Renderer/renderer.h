#pragma once
#include "core.h"
#include "glm/glm.hpp"

//Forward declarations
struct GLFWwindow;
namespace RE {

	class RE_API Renderer 
	{
	public:

		int mainLoop();
	};
	
	RE_API Renderer* createRenderer();
	
}


