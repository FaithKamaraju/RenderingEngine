#pragma once
#include "core/core.h"
#include "core/Object.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/Shader.h"
#include "core/Cameras/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RE {
	class RE_API PointLight : public Object
	{
    public:
        glm::vec3 m_lightColor = glm::vec3(1.f);
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float constant;
        float linear;
        float quadratic;
        Shader m_shaderID;
        unsigned int PointLightUBO;

    private:
        
        VertexArrayObject m_VAOId;

    public:
        PointLight();

        void tick(float deltaTime) override;
        void processInput(float deltaTime) override;

        void setUniforms();
	};
}


