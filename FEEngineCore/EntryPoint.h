#pragma once

#ifdef FE_PLATFORM_WINDOWS

#ifdef FE_EDITOR
	#include "ApplicationCore/AppInstance.h"
#elif (defined FE_GAME)
	#include "ApplicationCore/GameInstance.h"
#endif
extern FE::AppInstance* FE::CreateAppInstance();

int main(int argc, char** argv) {

	auto app = FE::CreateAppInstance();
	app->Run();
	delete app;
	return 0;
}
	
#else
	#error FE Engine only supports Windows!
#endif


