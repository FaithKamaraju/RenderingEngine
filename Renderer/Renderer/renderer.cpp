
#include "renderer.h"
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InputHandler.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/VerticesMetaData.h"
#include "Window.h"
#include "core/Cameras/Camera.h"


unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


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
            glfwSwapInterval(1);

            InputHandler::GetInputHandlerInstance(window->getWindowRef());

            GLCall(glEnable(GL_DEPTH_TEST));

            float vertices[] = {
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
            
            unsigned int diffuseMap = loadTexture("Resources/Textures/Container2.png");
            unsigned int specularMap = loadTexture("Resources/Textures/Container2_specular.png");

            VertexAttribute attr[3];
            attr[0] = VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);                       // position attr
            attr[1] = VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal attr
            attr[2] = VertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texCoord attr
            //attr[1] = VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // texCoord attr

            VertexArrayObject VAO;
            VAO.Bind();
            VAO.BindVertexBuffer(vertices, sizeof(vertices), attr, sizeof(attr) / sizeof(VertexAttribute), GL_STATIC_DRAW);
            //vao[0].BindElementBuffer(indices, sizeof(indices), GL_STATIC_DRAW);
            VAO.UnBind();

            Shader lightShader;
            lightShader.AttachShaders("Resources/Shaders/LightSource.shader");
            lightShader.UseShaderProgram();
            glm::vec3 lightColor = glm::vec3(1.f);
            lightShader.setVec3("lightColor", 1, glm::value_ptr(lightColor));
            glm::mat4 lightSourceMT = glm::mat4(1.0f);
            
            glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
            lightSourceMT = glm::translate(lightSourceMT, lightPos);
            lightSourceMT = glm::scale(lightSourceMT, glm::vec3(0.2f, 0.2f, 0.2f));


            Shader containerShader;
            containerShader.AttachShaders("Resources/Shaders/BasicShader.shader");
            containerShader.UseShaderProgram();
            //glm::vec3 containerColor = glm::vec3(1.0f, 0.5f, 0.31f);
            //containerShader.setVec3("objectColor", 1, glm::value_ptr(containerColor));
            //containerShader.setVec3("lightColor", 1, glm::value_ptr(lightColor));
            //containerShader.setVec3("lightPos", 1, glm::value_ptr(lightPos));

            //containerShader.setVec3("material.ambient", 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
            containerShader.setInt("material.diffuseMap", 0);
            containerShader.setInt("material.specularMap", 1);
            containerShader.setFloat("material.shininess", 32.0f);

            containerShader.setVec3("light.position", 1, glm::value_ptr(lightPos));
            containerShader.setVec3("light.ambient", 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
            containerShader.setVec3("light.diffuse", 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
            containerShader.setVec3("light.specular", 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

            glm::mat4 containerModelMT = glm::mat4(1.0f);
            glm::mat3 containerNormalMT = glm::mat3(glm::transpose(glm::inverse(containerModelMT)));


          
            std::unique_ptr<Camera> camera = std::make_unique<Camera>(window, 60.0f);
            camera->translate(0.0f, 0.0f, 5.0f);
            
            
            float deltaTime = 0.0f;	// Time between current frame and last frame
            float lastFrame = 0.0f; // Time of last frame
            
            /* Loop until the user closes the window */
            while (!window->getWindowShouldClose())
            {
                float currentFrame = (float)glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                //std::cout << 1/deltaTime << '\n';

                window->processInput();
                camera->processInput(deltaTime);

                camera->tick(deltaTime);

                /* Render here */
                GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
                GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


                VAO.Bind();
                containerShader.UseShaderProgram();
                containerShader.setMatrix4fv("model", 1, false, glm::value_ptr(containerModelMT));
                containerShader.setMatrix4fv("view", 1, false, glm::value_ptr(camera->m_view));
                containerShader.setMatrix4fv("projection", 1, false, glm::value_ptr(camera->m_projection));
                containerShader.setMatrix3fv("normalMatrix", 1, false, glm::value_ptr(containerNormalMT));
                containerShader.setVec3("cameraPos", 1, glm::value_ptr(camera->getTransform().position));
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, diffuseMap);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, specularMap);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                lightShader.UseShaderProgram();
                lightShader.setMatrix4fv("model", 1, false, glm::value_ptr(lightSourceMT));
                lightShader.setMatrix4fv("view", 1, false, glm::value_ptr(camera->m_view));
                lightShader.setMatrix4fv("projection", 1, false, glm::value_ptr(camera->m_projection));
                glDrawArrays(GL_TRIANGLES, 0, 36);


                window->swapBuffers();

                glfwPollEvents();
            }
        }
        glfwTerminate();
        return 0;
    }
}

