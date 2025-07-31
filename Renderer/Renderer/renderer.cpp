
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"

#include "OpenGL/Shader.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/VerticesMetaData.h"
#include "Window.h"
#include "Camera.h"



namespace RE {

    Renderer* createRenderer()
    {
        return new Renderer();
    }

 
    int Renderer::mainLoop() {

        {
            std::shared_ptr<Window> window = std::make_shared<Window>(800, 600, "Hello World!");

            window->initGLAD();
            glfwSwapInterval(1);

            GLCall(glEnable(GL_DEPTH_TEST));

            Shader shader;
            shader.AttachShaders("Resources/Shaders/BasicShaderWithTexture.shader");
            float vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };
            
            unsigned int texID;
            GLCall(glGenTextures(1, &texID));
            GLCall(glActiveTexture(GL_TEXTURE4));
            GLCall(glBindTexture(GL_TEXTURE_2D, texID));

            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

            stbi_set_flip_vertically_on_load(true);
            int width, height, nrChannels;
            unsigned char* data = stbi_load("Resources/Textures/container.jpg", &width, &height,
                &nrChannels, 0);
            if (data) {
                GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
                GLCall(glGenerateMipmap(GL_TEXTURE_2D));

            }
            else {
                std::cout << "Failed to load the texture" << '\n';
            }
            stbi_image_free(data);

            
            VertexAttribute attr[2];
            attr[0] = VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);                   // position attr
            attr[1] = VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // texCoord attr

            VertexArrayObject vao[1];
            vao[0].Bind();
            vao[0].BindVertexBuffer(vertices, sizeof(vertices), attr, sizeof(attr) / sizeof(VertexAttribute), GL_STATIC_DRAW);
            //vao[0].BindElementBuffer(indices, sizeof(indices), GL_STATIC_DRAW);
            vao[0].UnBind();

            shader.UseShaderProgram();
            shader.setInt("ourTexture", 4);


            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            std::unique_ptr<Camera> camera = std::make_unique<Camera>(window, 45.0f);
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

                
                shader.setMatrix4fv("model", 1, false, glm::value_ptr(model));
                shader.setMatrix4fv("view", 1, false, glm::value_ptr(camera->m_view));
                shader.setMatrix4fv("projection", 1, false, glm::value_ptr(camera->m_projection));

                for (auto& obj : vao) {
                    GLCall(glActiveTexture(GL_TEXTURE4));
                    obj.Bind();
                    /*GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));*/
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                window->swapBuffers();

                glfwPollEvents();
            }
        }
        glfwTerminate();
        return 0;
    }
}

