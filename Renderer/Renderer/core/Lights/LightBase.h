#pragma once

#include "core/core.h"
#include "core/Object.h"
#include "core/Mesh/Mesh.h"
#include "core/Lights/LightUBOManager.h"

namespace RE {
	class RE_API LightBase : public Object
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


