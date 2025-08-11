
#include "renderer.h"
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
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
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

bool DoTheImportThing(const std::string& pFile) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (nullptr == scene) {
        //DoTheErrorLogging(importer.GetErrorString());
        return false;
    }

    // Now we can access the file's contents.
    //DoTheSceneProcessing(scene);

    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}


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

            


            VertexArrayObject VAO;
            VAO.Bind();
            VAO.BindVertexBuffer(vertices, sizeof(vertices), attr, sizeof(attr) / sizeof(VertexAttribute), GL_STATIC_DRAW);
            VAO.UnBind();

            Shader containerShader;
            containerShader.AttachShaders("Resources/Shaders/BasicShader.shader");
            containerShader.UseShaderProgram();
            containerShader.setInt("material.diffuseMap", 0);
            containerShader.setInt("material.specularMap", 1);
            containerShader.setFloat("material.shininess", 32.0f);

            GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(containerShader.m_ShaderProgramID, "CameraData"));
            GLCall(glUniformBlockBinding(containerShader.m_ShaderProgramID, MatricesBlockIndex, BPI_GlobalCameraMatrices));

            GLCall(unsigned int DirLightBlockIndex = glGetUniformBlockIndex(containerShader.m_ShaderProgramID, "DirectionalLight"));
            GLCall(glUniformBlockBinding(containerShader.m_ShaderProgramID, DirLightBlockIndex, BPI_DirLight));

            GLCall(unsigned int LightsBlockIndex = glGetUniformBlockIndex(containerShader.m_ShaderProgramID, "Lights"));
            GLCall(glUniformBlockBinding(containerShader.m_ShaderProgramID, LightsBlockIndex, BPI_Lights));

            glm::mat4 containerModelMT = glm::mat4(1.0f);
            containerModelMT = glm::scale(containerModelMT, glm::vec3(5.f));
            glm::mat3 containerNormalMT = glm::mat3(glm::transpose(glm::inverse(containerModelMT)));

            DirectionalLight dirLight;
            dirLight.setPositionGlobal(10.f, 10.f, 10.f);

            PointLight pointLight;
            //pointLight.setPositionGlobal(6.f, 4.0f, 0.0f);
           /* GLCall(glNamedBufferSubData(pointLight.PointLightUBO, 0, sizeof(glm::vec4), glm::value_ptr(pointLight.transform.globalPosition)));*/
            SpotLight spotLight;
            //spotLight.setPositionGlobal(0.0f, 8.f, 0.0f);
            /*GLCall(glNamedBufferSubData(spotLight.SpotLightUBO, 0, sizeof(glm::vec4), glm::value_ptr(spotLight.transform.globalPosition)));*/

            std::unique_ptr<Camera> camera = std::make_unique<Camera>(window, 60.0f);
            camera->translateGlobal(0.0f, 0.0f, 10.0f);

            float deltaTime = 0.0f;	// Time between current frame and last frame
            float lastFrame = 0.0f; // Time of last frame
            /* Loop until the user closes the window */
            while (!window->getWindowShouldClose())
            {
                float currentFrame = (float)glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                //std::cout << 1 / deltaTime << '\n';

                window->processInput();

                camera->processInput(deltaTime);
                camera->tick(deltaTime);  

                /* Render here */
                GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
                GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


                VAO.Bind();
                containerShader.UseShaderProgram();
                containerShader.setMatrix4fv("model", 1, false, glm::value_ptr(containerModelMT));
                containerShader.setMatrix3fv("normalMatrix", 1, false, glm::value_ptr(containerNormalMT));
                //containerShader.setVec3("cameraPos", 1, glm::value_ptr(camera->getTransform().globalPosition));
                GLCall(glActiveTexture(GL_TEXTURE0));
                GLCall(glBindTexture(GL_TEXTURE_2D, diffuseMap));
                GLCall(glActiveTexture(GL_TEXTURE1));
                GLCall(glBindTexture(GL_TEXTURE_2D, specularMap));
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

                dirLight.render();
                pointLight.render();
                spotLight.render();
                

                window->swapBuffers();


                glfwPollEvents();
            }
        }
        glfwTerminate();
        return 0;
    }
}

