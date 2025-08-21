
#include "Engine.h"
#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




FE_API FE::Engine* FE::CreateEngineInstance()
{
    return new Engine();
}
   
int FE::Engine::InitializeEngine()
{
    return 0;
}

int FE::Engine::StartEngineLoop() 
{
                  
    

    //float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //// Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ////ImGui::StyleColorsLight();
    //ImGuiStyle& style = ImGui::GetStyle();
    //style.FontScaleDpi = main_scale;

    //// Setup Platform/Renderer backends
    //ImGui_ImplGlfw_InitForOpenGL(window->getWindowRef(), true);
    //const char* glsl_version = "#version 460";
    //ImGui_ImplOpenGL3_Init(glsl_version);
    //bool show_demo_window = true;
    //bool show_another_window = false;
    //ImVec4 clear_color = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

    //InputHandler::GetInputHandlerInstance(window->getWindowRef());

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    /* Loop until the user closes the window */
    while (!window->getWindowShouldClose())
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
                
        window->processInput();

       

        window->swapBuffers();


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
