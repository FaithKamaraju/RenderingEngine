#include "PointLight.h"
#include "core/Constants.h"
#include "core/Lights/LightUBOManager.h"


void RE::PointLight::_updateModelMatrix()
{

    Object::_updateModelMatrix();
    LightUBOManager::GetInstance()->updateUBO(weak_from_this());
}

RE::PointLight::PointLight()
	:ambient(0.1f), diffuse(1.f), specular(1.f)
{
    		
    constant = 1.0f;
    linear = 0.022f;
    quadratic = 0.0019f;

    m_shaderID.AttachShaders("Resources/Shaders/Lights/LightSource.shader");
    m_shaderID.UseShaderProgram();
    m_shaderID.setVec3("lightColor", 1, glm::value_ptr(m_lightColor));


    GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(m_shaderID.m_ShaderProgramID, "Matrices"));
    GLCall(glUniformBlockBinding(m_shaderID.m_ShaderProgramID, MatricesBlockIndex, BPI_GlobalCameraMatrices));
}

RE::PointLight::~PointLight()
{
    LightUBOManager::GetInstance()->deleteLight(weak_from_this());
}

void RE::PointLight::beginPlay()
{
    registerLight();
}

void RE::PointLight::tick(float deltaTime)
{
}

void RE::PointLight::processInput(float deltaTime)
{
}

void RE::PointLight::registerLight()
{
    this->UBO_index = LightUBOManager::GetInstance()->addPointLightToMemory(shared_from_this());
}
//void RE::PointLight::setUniforms()
//{
//    m_shaderID.UseShaderProgram();
//    m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(m_modelMatrix));
//    //m_shaderID.setMatrix4fv("view", 1, false, glm::value_ptr(view));
//    //m_shaderID.setMatrix4fv("projection", 1, false, glm::value_ptr(projection));
//}
