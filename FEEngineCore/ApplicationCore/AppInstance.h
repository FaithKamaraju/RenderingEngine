#pragma once

#include "EngineMacros.h"

namespace FE {

	class FE_API AppInstance
	{
	public:
		virtual int Run() = 0;
	};

	// To be defined in Game files.
	AppInstance* CreateAppInstance();
}


