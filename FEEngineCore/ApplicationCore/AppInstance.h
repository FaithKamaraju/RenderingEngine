#pragma once

#include "EngineMacros.h"


namespace FE {

	class Engine;

	class FE_API AppInstance
	{
	public:
		virtual int Run() = 0;
	

	private:
		
	};

	// To be defined in Game files.
	AppInstance* CreateAppInstance();

	
}


