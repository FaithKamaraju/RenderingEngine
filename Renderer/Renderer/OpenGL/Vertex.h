#pragma once

#include "core/core.h"

#include "glm/glm.hpp"

namespace RE {

	struct RE_API Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}
