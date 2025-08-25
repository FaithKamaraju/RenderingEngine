
#include "EngineCore/GameplayStatics/EngineGlobals.h"
#include <memory>

namespace FE {

	static inline std::shared_ptr<InputHandler> GetInputHandler() {

		return EngineGlobals::engineObj->m_InputHandlerInst;
	}

	static inline std::shared_ptr<IWindow> GetWindowRef() {

		return EngineGlobals::engineObj->m_WindowObj;
	}
}
