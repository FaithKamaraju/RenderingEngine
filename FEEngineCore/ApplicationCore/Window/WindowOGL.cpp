#include "WindowOGL.h"




FE::WindowOGL::~WindowOGL()
{
}

void FE::WindowOGL::Init(int width, int height, const char* title, FEenum windowMode)
{
}
void FE::WindowOGL::setInputMode(FEenum mode, FEenum value) const
{
}



///* Initialize the library */
//if (!glfwInit())
//{
//    std::cerr << "Failed to initialize GLFW!" << std::endl;
//}
//
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
///* Create a windowed mode window and its OpenGL context */
//m_Window = glfwCreateWindow((int)main_scale * m_Width, (int)main_scale * m_Height, m_WindowTitle, NULL, NULL);
//if (!m_Window)
//{
//    std::cerr << "Failed to create GLFW window" << std::endl;
//    glfwTerminate();
//}
//
///* Make the window's context current */
//glfwMakeContextCurrent(m_Window);
//glfwSetCursorPosCallback(m_Window, mouse_callback);
//glfwSetScrollCallback(m_Window, scroll_callback);
//
//bool FE::Window::initGLAD() const
//{
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cerr << "Failed to initialize GLAD" << std::endl;
//        return false;
//    }
//
//    setFrameBufferSizeCallBack();
//
//    return true;
//}
//
//FE::Window::Window(int width, int height, const char* title)
//    : m_Width(width), m_Height(height), m_WindowTitle(title)
//{
//
//
//}
//
//FE::Window::~Window()
//{
//}
//
//
////GLFWwindow* FE::Window::getWindowRef() const
////{
////	return this->m_Window;
////}
//
//bool FE::Window::getWindowShouldClose() const
//{
//    return glfwWindowShouldClose(this->m_Window);
//}
//
//
//
//void FE::Window::setFrameBufferSizeCallBack() const
//{
//    glViewport(0, 0, m_Width, m_Height);
//    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
//}
//
//
//void FE::Window::setInputMode(FEenum mode, FEenum value) const
//{
//    glfwSetInputMode(this->m_Window, mode, value);
//}
//
//void FE::Window::processInput()
//{
//    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(m_Window, true);
//}
//
//void FE::Window::swapBuffers()
//{
//    glfwSwapBuffers(m_Window);
//}

//SDL_Window* window;                    // Declare a pointer
//bool done = false;
//
//SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3
//
//// Create an application window with the following settings:
//window = SDL_CreateWindow(
//    "An SDL3 window",                  // window title
//    640,                               // width, in pixels
//    480,                               // height, in pixels
//    SDL_WINDOW_OPENGL                  // flags - see below
//);
//
//// Check that the window was successfully created
//if (window == NULL) {
//    // In the case that the window could not be made...
//    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
//    return 1;
//}
//
//while (!done) {
//    SDL_Event event;
//
//    while (SDL_PollEvent(&event)) {
//        if (event.type == SDL_EVENT_QUIT) {
//            done = true;
//        }
//    }
//
//    // Do game logic, present a frame, etc.
//}
//
//// Close and destroy the window
//SDL_DestroyWindow(window);
//
//// Clean up
//SDL_Quit();
//return 0;