#pragma once

#include "core/core.h"
#include "core/ObjectTransform.h"
#include "glm/glm.hpp"

namespace RE {

	class RE_API Object
	{
	public:
		ObjectTransform transform;
	public:
		Object();

		ObjectTransform getTransform() const;
		void setTransform(const ObjectTransform& otherTransform);

		void setPosition(float x, float y, float z);
		void setRotation(float pitch, float yaw, float roll);
		void setScale(float x, float y, float z);

		void translate(float x, float y, float z);
		void translate(glm::vec3 translateBy);
		void rotate(float pitch, float yaw, float roll);
		void rotate(glm::vec3 rotateBy);

		virtual void tick(float deltaTime) = 0;
		virtual void processInput(float deltaTime) = 0;
		
	};
}


