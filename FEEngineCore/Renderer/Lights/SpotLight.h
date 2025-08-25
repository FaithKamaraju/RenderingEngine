#pragma once
#include "EngineMacros.h"
#include "LightBase.h"
#include "EngineCore/GameplayFramework/Cameras/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace FE {

	class FE_API SpotLight : public LightBase, public std::enable_shared_from_this<SpotLight>
	{
    public:

        glm::vec3 m_lightColor = glm::vec3(1.f);
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float innerangle;
        float outerangle;
        float constant;
        float linear;
        float quadratic;

    private:
        void _updateModelMatrix() override;

    public:
        SpotLight();
        ~SpotLight();

        void beginPlay() override;
        void tick(float deltaTime) override;
        void processInput(const InputEvent& event, float deltaTime) override;

        void registerLight();
        /*void setUniforms();*/
	};
}


