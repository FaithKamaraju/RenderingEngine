#pragma once

#include "EngineMacros.h"

#include "glm/glm.hpp"

namespace FE {

	struct FE_API ObjectTransform
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		glm::vec3 globalPosition = glm::vec3(0.0f);
		glm::vec3 globalRotation = glm::vec3(0.0f);
	};
}


