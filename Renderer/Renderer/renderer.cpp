#include "renderer.h"
#include "Shader.h"

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"



namespace RE {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    Renderer* createRenderer()
    {
        return new Renderer();
    }

    void Renderer::processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    int Renderer::mainLoop() {

        /* Initialize the library */
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW!" << std::endl;
            return -1;
        }
            

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        constexpr int WIDTH = 800;
        constexpr int HEIGHT = 600;
        const char* TITLE = "HELLO WORLD!";

        /* Create a windowed mode window and its OpenGL context */
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        std::cout << glGetString(GL_VERSION) << "\n";
        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        Shader shader;
        shader.AttachShaders("Resources/Shaders/BasicShader.shader");
        
        float vertices1[] = {
             0.75f,  0.5f, 0.0f,  // top right
             0.75f, -0.5f, 0.0f,  // bottom right
             0.25f, -0.5f, 0.0f,  // bottom left
             0.25f,  0.5f, 0.0f   // top left 
        };
        float vertices2[] = {
             -0.25f,  0.5f, 0.0f,  // top right
             -0.25f, -0.5f, 0.0f,  // bottom right
             -0.75f, -0.5f, 0.0f,  // bottom left
             -0.75f,  0.5f, 0.0f   // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
             0, 1, 3,   // first triangle
             1, 2, 3    // second triangle
        };

        unsigned int arrayObjs[2];
        glGenVertexArrays(2, arrayObjs);

        unsigned int buffers[2];
        glGenBuffers(2,buffers);

        unsigned int EBO;
        glGenBuffers(1, &EBO);

        glBindVertexArray(arrayObjs[0]);
            glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        glBindVertexArray(arrayObjs[1]);
            glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        
        //glUseProgram(shaderProgram);
        

        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.UseShaderProgram();
            for (auto obj : arrayObjs) {
                glBindVertexArray(obj);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            
            
            //glBindVertexArray(0);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}

