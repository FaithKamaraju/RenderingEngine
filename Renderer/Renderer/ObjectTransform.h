#pragma once

#include "core.h"
#include "glm/glm.hpp"

namespace RE {

	struct RE_API ObjectTransform
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
	};
}


