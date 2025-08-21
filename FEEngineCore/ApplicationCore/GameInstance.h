#pragma once

#include "EngineMacros.h"
#include "AppInstance.h"

namespace FE {
	class GameInstance : public AppInstance
	{
	public:
		int Run() override;
	};

	AppInstance* CreateAppInstance() {

		return new GameInstance();
	}
}


