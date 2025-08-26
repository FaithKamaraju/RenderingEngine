#pragma once
#include "EngineMacros.h"
#include "EngineCore/Renderer/SceneGraph/SceneGraph.h"

#include "glm/glm.hpp"
#include <memory>



namespace FE {

	class FE_API Renderer 
	{
	public:

		int render();

	public:
		std::unique_ptr<SceneGraph> m_sceneGraph;
	};
	
	FE_API Renderer* createRenderer();
	
}


