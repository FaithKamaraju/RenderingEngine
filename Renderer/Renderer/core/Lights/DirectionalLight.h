#pragma once

#include "core/core.h"

#include "core/Lights/LightBase.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/Shader.h"
#include "core/Cameras/Camera.h"
#include "core/Mesh/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace RE {
	class RE_API DirectionalLight : public LightBase
	{
	public:
        glm::vec3 m_lightColor = glm::vec3(1.f);
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        unsigned int DirLightUBO;

    private:

    public:
        DirectionalLight();

        void tick(float deltaTime) override;
        void processInput(float deltaTime) override;

        void updateDirection();

        void beginPlay() override;

        //void setUniforms();
	};
}



