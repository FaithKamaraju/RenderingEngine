#include "renderer.h"

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
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        constexpr int WIDTH = 800;
        constexpr int HEIGHT = 600;
        const char* TITLE = "HELLO WORLD!";

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}

