#pragma once

#include "EngineMacros.h"

#include "glm/glm.hpp"

namespace FE {

	struct FE_API Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}
