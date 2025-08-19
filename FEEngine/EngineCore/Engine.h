#pragma once
#include "EngineCore.h"
#include "glm/glm.hpp"



//Forward declarations

namespace FE {

	class FE_API Engine
	{
	public:

		int StartEngineLoop();
		

	};
	
	FE_API Engine* CreateEngineInstance();
	
}


