#include "PointLight.h"


void FE::PointLight::_updateModelMatrix()
{

    Object::_updateModelMatrix();
    LightUBOManager::GetInstance()->updateUBO(weak_from_this());
}

FE::PointLight::PointLight()
	:ambient(0.1f), diffuse(1.f), specular(1.f)
{
    		
    constant = 1.0f;
    linear = 0.022f;
    quadratic = 0.0019f;

}

FE::PointLight::~PointLight()
{
    LightUBOManager::GetInstance()->deleteLight(weak_from_this());
}

void FE::PointLight::beginPlay()
{
    registerLight();
}

void FE::PointLight::tick(float deltaTime)
{
}

void FE::PointLight::processInput(const InputEvent& event, float deltaTime)
{
}

void FE::PointLight::registerLight()
{
    this->UBO_index = LightUBOManager::GetInstance()->addPointLightToMemory(shared_from_this());
}
//void FE::PointLight::setUniforms()
//{
//    m_shaderID.UseShaderProgram();
//    m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(m_modelMatrix));
//    //m_shaderID.setMatrix4fv("view", 1, false, glm::value_ptr(view));
//    //m_shaderID.setMatrix4fv("projection", 1, false, glm::value_ptr(projection));
//}
