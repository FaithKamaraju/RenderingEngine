#pragma once

#include "core/core.h"
#include "OpenGL/Shader.h"
#include "core/ObjectTransform.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RE {

	class RE_API Object
	{
	public:
		ObjectTransform transform;
	protected:
		glm::mat4 m_modelMatrix;
		glm::mat4 m_modelMatrixLocal;
		
	public:
		Shader m_shaderID;
		Object();

		ObjectTransform getTransform();
		glm::mat4 getModelMT() const;
		glm::mat4 getModelMTLocal() const;
		void setTransform(const ObjectTransform& otherTransform);

		void setPositionLocal(float x, float y, float z);
		void setPositionGlobal(float x, float y, float z);
		void setRotationLocal(float pitch, float yaw, float roll);
		void setRotationGlobal(float pitch, float yaw, float roll);
		void setScale(float x, float y, float z);
		void setScale(float scale);

		void translateLocal(float x, float y, float z);
		void translateLocal(glm::vec3 translateBy);
		void translateGlobal(float x, float y, float z);
		void translateGlobal(glm::vec3 translateBy);

		void rotateLocal(float pitch, float yaw, float roll);
		void rotateLocal(glm::vec3 rotateBy);
		void rotateGlobal(float pitch, float yaw, float roll);
		void rotateGlobal(glm::vec3 rotateBy);

		

	protected:

		virtual void beginPlay() = 0;
		virtual void tick(float deltaTime) = 0;
		virtual void processInput(float deltaTime) = 0;

		virtual void _updateModelMatrix();
	};
}


