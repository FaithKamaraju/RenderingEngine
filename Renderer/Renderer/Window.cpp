#include "Window.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <iostream>


RE::Window::Window(int width, int height, const char* title)
    : m_Width(width), m_Height(height), m_WindowTitle(title)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow((int)main_scale * m_Width, (int)main_scale * m_Height, m_WindowTitle, NULL, NULL);
    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);

}

RE::Window::~Window()
{
    glfwTerminate();
}


GLFWwindow* RE::Window::getWindowRef() const
{
	return this->m_Window;
}

bool RE::Window::getWindowShouldClose() const
{
    return glfwWindowShouldClose(this->m_Window);
}

bool RE::Window::initGLAD() const
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    std::cout << glGetString(GL_VERSION) << "\n";
    int nrAttributes;
    GLCall(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes));
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    setFrameBufferSizeCallBack();
    
    return true;
}

void RE::Window::setFrameBufferSizeCallBack() const
{
    GLCall(glViewport(0, 0, m_Width, m_Height));
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}


void RE::Window::setInputMode(GLenum mode, GLenum value) const
{
    glfwSetInputMode(this->m_Window, mode, value);
}

void RE::Window::processInput()
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}

void RE::Window::swapBuffers()
{
    glfwSwapBuffers(m_Window);
}
