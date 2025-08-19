#pragma once

#include "EngineCore/EngineCore.h"

#include "EngineCore/Object.h"
#include "Renderer/Constants.h"
#include "Renderer/OpenGL/ErrorChecking.h"
#include "LightUBOManager.h"

namespace FE {
	class FE_API LightBase : public Object
	{
	public:
		
	protected:
		int UBO_index;
		LightBase();

		void beginPlay() override;
		
	public:
		friend class LightUBOManager;
	};
}


