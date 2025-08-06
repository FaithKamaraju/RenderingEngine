#include "DirectionalLight.h"
#include "core/Constants.h"
#include <iostream>


RE::DirectionalLight::DirectionalLight()
    :direction(0.0f, 0.0f,-1.0f),ambient(0.1f), diffuse(1.f), specular(1.f)
{
    transform.rotation = glm::vec3(0.0f);

    constexpr float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    VertexAttribute attr[2];
    attr[0] = VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);                       // position attr
    attr[1] = VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal attr
    m_VAOId.Bind();
    m_VAOId.BindVertexBuffer(vertices, sizeof(vertices), attr, sizeof(attr) / sizeof(VertexAttribute), GL_STATIC_DRAW);
    m_VAOId.UnBind();

    m_shaderID.AttachShaders("Resources/Shaders/Lights/LightSource.shader");
    m_shaderID.UseShaderProgram();
    m_shaderID.setVec3("lightColor", 1, glm::value_ptr(m_lightColor));

    

    glGenBuffers(1, &DirLightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, DirLightUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 4, NULL, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, GlobalDirLightBindingPointIndex, DirLightUBO, 0, sizeof(glm::vec4) * 4);
    glBufferSubData(GL_UNIFORM_BUFFER, 0,                     sizeof(glm::vec4), glm::value_ptr(direction));
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(ambient));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(specular));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

     GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(m_shaderID.m_ShaderProgramID, "Matrices"));
     GLCall(glUniformBlockBinding(m_shaderID.m_ShaderProgramID, MatricesBlockIndex, GlobalMatricesBindingPointIndex));
}

void RE::DirectionalLight::tick(float deltaTime)
{
    static float frame = 0.f;
    rotateLocal(0.0f, 0.0f, 50.f * deltaTime);
    glm::mat4 temp = glm::mat4(1.f);
    temp = glm::rotate(temp, glm::radians(50.f * deltaTime), glm::vec3(0.f, 1.f, 0.f));
    direction = temp * glm::vec4(direction, 1.0f);
    direction = glm::normalize(direction);
    if (frame >= 1.f) {
        std::cout << transform.rotation.x << ", " << transform.rotation.y << ", " << transform.rotation.z << "\n";
        std::cout << direction.x << ", " << direction.y << ", " << direction.z << "\n";
        std::cout << "--------------------\n";
        frame = 0.f;
    }
    frame += deltaTime;
    glNamedBufferSubData(DirLightUBO, 0, sizeof(glm::vec4), glm::value_ptr(direction));
}
    

void RE::DirectionalLight::processInput(float deltaTime)
{
}

void RE::DirectionalLight::setUniforms()
{
    m_shaderID.UseShaderProgram();
    m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(m_modelMatrix));
    //m_shaderID.setMatrix4fv("view", 1, false, glm::value_ptr(view));
    //m_shaderID.setMatrix4fv("projection", 1, false, glm::value_ptr(projection));
}
