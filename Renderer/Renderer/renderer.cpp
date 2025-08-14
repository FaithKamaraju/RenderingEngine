
#include "renderer.h"
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Constants.h"
#include "InputHandler.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/VerticesMetaData.h"
#include "Window.h"
#include "core/Cameras/Camera.h"
#include "core/Lights/DirectionalLight.h"
#include "core/Lights/PointLight.h"
#include "core/Lights/SpotLight.h"
#include "core/Mesh/Model.h"

namespace RE {

    Renderer* createRenderer()
    {
        return new Renderer();
    }

 
    int Renderer::mainLoop() {

        {
            stbi_set_flip_vertically_on_load(true);
            std::shared_ptr<Window> window = std::make_shared<Window>(800, 600, "Hello World!");

            window->initGLAD();
            window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSwapInterval(0);

            InputHandler::GetInputHandlerInstance(window->getWindowRef());

            GLCall(glEnable(GL_DEPTH_TEST));

            Model model("Resources/Models/backpack/backpack.obj");

            Shader shader;
            shader.AttachShaders("Resources/Shaders/BasicShader.shader");
            GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(shader.m_ShaderProgramID, "CameraData"));
            GLCall(glUniformBlockBinding(shader.m_ShaderProgramID, MatricesBlockIndex, BPI_GlobalCameraMatrices));

            GLCall(unsigned int DirLightBlockIndex = glGetUniformBlockIndex(shader.m_ShaderProgramID, "DirectionalLight"));
            GLCall(glUniformBlockBinding(shader.m_ShaderProgramID, DirLightBlockIndex, BPI_DirLight));

            GLCall(unsigned int LightsBlockIndex = glGetUniformBlockIndex(shader.m_ShaderProgramID, "Lights"));
            GLCall(glUniformBlockBinding(shader.m_ShaderProgramID, LightsBlockIndex, BPI_Lights));

            glm::mat4 ModelMT = glm::mat4(1.0f);
            ModelMT = glm::scale(ModelMT, glm::vec3(1.f));
            glm::mat3 NormalMT = glm::mat3(glm::transpose(glm::inverse(ModelMT)));
            
            /*
            shader.setInt("material.texture_diffuse1", 0);
            shader.setInt("material.texture_specular1", 1);
            shader.setFloat("material.shininess", 32.0f);*/

            /*auto dirLight = std::make_shared<DirectionalLight>();
            dirLight->setPositionGlobal(10.f, 10.f, 10.f);*/

            auto pointLight = std::make_shared<PointLight>();
            pointLight->setPositionGlobal(10.f, 0.0f, 0.0f);

            auto pointLight1 = std::make_shared<PointLight>();
            pointLight1->setPositionGlobal(-10.f, 0.0f, 0.0f);

            auto pointLight2 = std::make_shared<PointLight>();
            pointLight2->setPositionGlobal(0.f, -10.0f, 0.0f);

            auto pointLight3 = std::make_shared<PointLight>();
            pointLight3->setPositionGlobal(0.f, 10.0f,0.0f);

            std::unique_ptr<Camera> camera = std::make_unique<Camera>(window, 60.0f);
            camera->translateGlobal(0.0f, 0.0f, 10.0f);

            camera->beginPlay();
            pointLight->beginPlay();
            pointLight1->beginPlay();
            pointLight2->beginPlay();
            pointLight3->beginPlay();
            /*spotLight->beginPlay();
            dirLight->beginPlay();*/

            float deltaTime = 0.0f;	// Time between current frame and last frame
            float lastFrame = 0.0f; // Time of last frame
            float time = 0.0f;
            /* Loop until the user closes the window */
            while (!window->getWindowShouldClose())
            {
                float currentFrame = (float)glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                time += deltaTime;
                
                std::cout << 1 / deltaTime << '\n';

                window->processInput();

                camera->processInput(deltaTime);
                camera->tick(deltaTime);  

                /* Render here */
                GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
                GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

                
                shader.UseShaderProgram();
                shader.setMatrix4fv("model", 1, false, glm::value_ptr(ModelMT));
                shader.setMatrix3fv("normalMatrix", 1, false, glm::value_ptr(NormalMT));
                model.Draw(shader);

                //spotLight->m_shaderID.UseShaderProgram();
                //spotLight->m_shaderID.setMatrix4fv("model", 1, false, glm::value_ptr(spotLight->getModelMT()));
                ////spotLight.m_shaderID.setMatrix3fv("normalMatrix", 1, false, glm::value_ptr(NormalMT));
                //spotLight->mesh->Draw(true);
                

                window->swapBuffers();


                glfwPollEvents();
            }
        }
        glfwTerminate();
        return 0;
    }
}

