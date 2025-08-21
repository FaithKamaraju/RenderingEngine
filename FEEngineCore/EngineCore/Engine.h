#pragma once
#include "EngineMacros.h"
#include "glm/glm.hpp"


namespace FE {

	class FE_API Engine
	{
	public:

		int InitializeEngine();
		int StartEngineLoop();
		

	};
	
	FE_API Engine* CreateEngineInstance();
	
}


