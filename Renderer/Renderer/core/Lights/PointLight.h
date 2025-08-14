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
	class RE_API PointLight : public LightBase, public std::enable_shared_from_this<PointLight>
	{
    public:
        glm::vec3 m_lightColor = glm::vec3(1.f);
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float constant;
        float linear;
        float quadratic;

    private:

        void _updateModelMatrix() override;

    public:
        PointLight();
        ~PointLight();

        void beginPlay() override;
        void tick(float deltaTime) override;
        void processInput(float deltaTime) override;

        void registerLight();

        //void setUniforms();
        
	};
}


