#include "SpotLight.h"
#include "core/Constants.h"
#include "core/Lights/LightUBOManager.h"


void RE::SpotLight::_updateModelMatrix()
{

    Object::_updateModelMatrix();
    LightUBOManager::GetInstance()->updateUBO(weak_from_this());
}

RE::SpotLight::SpotLight()
    :direction(0.0f, -1.f, 0.0f), ambient(0.1f), diffuse(1.f), specular(1.f), innerangle(glm::radians(10.f)), outerangle(glm::radians(20.f))
{
    constant = 1.f;
    linear = 0.045f;
    quadratic = 0.0075f;

    m_shaderID.AttachShaders("Resources/Shaders/Lights/LightSource.shader");
    m_shaderID.UseShaderProgram();
    m_shaderID.setVec3("lightColor", 1, glm::value_ptr(m_lightColor));

    

   

    GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(m_shaderID.m_ShaderProgramID, "Matrices"));
    GLCall(glUniformBlockBinding(m_shaderID.m_ShaderProgramID, MatricesBlockIndex, BPI_GlobalCameraMatrices));
    
}

RE::SpotLight::~SpotLight()
{
    LightUBOManager::GetInstance()->deleteLight(weak_from_this());
}

void RE::SpotLight::beginPlay()
{
    registerLight();
}

void RE::SpotLight::tick(float deltaTime)
{
}

void RE::SpotLight::processInput(float deltaTime)
{
}
void RE::SpotLight::registerLight()
{
    this->UBO_index = LightUBOManager::GetInstance()->addSpotLightToMemory(shared_from_this());
}

//void RE::SpotLight::setUniforms() 
//{
//    m_shaderID.UseShaderProgram();
//    m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(m_modelMatrix));
//}


