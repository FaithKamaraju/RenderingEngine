#pragma once
#include "EngineMacros.h"
#include "Symbols.h"
#include <memory>

namespace FE {
	class IWindow;
	class InputHandler;

	struct FE_API Config {
		GraphicsAPI api;
		int width;
		int height;
		const char* title;
	};

	class FE_API Engine
	{

	private:

		Config LoadConfig(const char* configpath);

	public:

		Config m_AppConfig;
		std::shared_ptr<IWindow> m_WindowObj;
		std::shared_ptr<InputHandler> m_InputHandlerInst;

		int InitializeEngine();
		int StartEngineLoop();

		
	};
	
	FE_API Engine* CreateEngineInstance();
	
}


