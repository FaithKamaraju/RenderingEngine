#include "SpotLight.h"


void FE::SpotLight::_updateModelMatrix()
{

    Object::_updateModelMatrix();
    LightUBOManager::GetInstance()->updateUBO(weak_from_this());
}

FE::SpotLight::SpotLight()
    :direction(0.0f, -1.f, 0.0f), ambient(0.1f), diffuse(1.f), specular(1.f), innerangle(glm::radians(10.f)), outerangle(glm::radians(20.f))
{
    constant = 1.f;
    linear = 0.045f;
    quadratic = 0.0075f;

}

FE::SpotLight::~SpotLight()
{
    LightUBOManager::GetInstance()->deleteLight(weak_from_this());
}

void FE::SpotLight::beginPlay()
{
    registerLight();
}

void FE::SpotLight::tick(float deltaTime)
{
}

void FE::SpotLight::processInput(const InputEvent& event, float deltaTime)
{
}
void FE::SpotLight::registerLight()
{
    this->UBO_index = LightUBOManager::GetInstance()->addSpotLightToMemory(shared_from_this());
}

//void FE::SpotLight::setUniforms() 
//{
//    m_shaderID.UseShaderProgram();
//    m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(m_modelMatrix));
//}


