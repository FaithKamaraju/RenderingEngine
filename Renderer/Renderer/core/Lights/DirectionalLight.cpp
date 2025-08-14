#include "DirectionalLight.h"
#include "core/Constants.h"
#include <iostream>

RE::DirectionalLight::DirectionalLight()
    :direction(-1.f), ambient(0.1f), diffuse(1.f), specular(1.f)
{
    transform.rotation = glm::vec3(0.0f);

    

    m_shaderID.AttachShaders("Resources/Shaders/Lights/LightSource.shader");
    m_shaderID.UseShaderProgram();
    m_shaderID.setVec3("lightColor", 1, glm::value_ptr(m_lightColor));

    GLCall(glGenBuffers(1, &DirLightUBO));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, DirLightUBO));
    GLCall(glBufferData(GL_UNIFORM_BUFFER, 64, NULL, GL_DYNAMIC_DRAW));
    GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, BPI_DirLight, DirLightUBO, 0, 64));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0 , 16, glm::value_ptr(direction)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 16, 16, glm::value_ptr(ambient)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 32, 16, glm::value_ptr(diffuse)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 48, 16, glm::value_ptr(specular)));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));

    GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(m_shaderID.m_ShaderProgramID, "Matrices"));
    GLCall(glUniformBlockBinding(m_shaderID.m_ShaderProgramID, MatricesBlockIndex, BPI_GlobalCameraMatrices));


     
}

void RE::DirectionalLight::tick(float deltaTime)
{
    /*rotateLocal(0.0f, 0.0f, 25.f * deltaTime);
    direction = glm::vec3(0.0f, -1.f, 0.0f);
    direction = this->m_modelMatrixLocal * glm::vec4(direction, 1.0f);
    direction = glm::normalize(direction);
    GLCall(glNamedBufferSubData(DirLightUBO, 0, sizeof(glm::vec4), glm::value_ptr(direction)));*/
}
    

void RE::DirectionalLight::processInput(float deltaTime)
{
    
}

void RE::DirectionalLight::updateDirection()
{
    direction = glm::vec3(0.0f, -1.f, 0.0f);
    direction = this->m_modelMatrixLocal * glm::vec4(direction, 1.0f);
    direction = glm::normalize(direction);
    glNamedBufferSubData(DirLightUBO, 0, sizeof(glm::vec4), glm::value_ptr(direction));
}

void RE::DirectionalLight::beginPlay()
{

}

//void RE::DirectionalLight::setUniforms()
//{
//    m_shaderID.UseShaderProgram();
//    m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(m_modelMatrix));
//    //m_shaderID.setMatrix4fv("view", 1, false, glm::value_ptr(view));
//    //m_shaderID.setMatrix4fv("projection", 1, false, glm::value_ptr(projection));
//}
