#pragma once

#include "EngineMacros.h"
#include "LightBase.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace FE {
	class FE_API DirectionalLight : public LightBase
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
        void processInput(const InputEvent& event, float deltaTime) override;

        void updateDirection();

        void beginPlay() override;

        //void setUniforms();
	};
}



