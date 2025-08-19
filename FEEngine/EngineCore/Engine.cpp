
#include "Engine.h"
#include <iostream>
#include <memory>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EngineCore/Window.h"
#include "EngineCore/InputHandler.h"


namespace FE {

    FE_API FE::Engine* CreateEngineInstance()
    {
        return new Engine();
    }
   
    int FE::Engine::StartEngineLoop() {

        {
                  
            std::shared_ptr<Window> window = std::make_shared<Window>(1280, 720, "Hello World!");

            

            window->initGLAD();
            window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSwapInterval(1);

            float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();
            ImGuiStyle& style = ImGui::GetStyle();
            style.FontScaleDpi = main_scale;

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window->getWindowRef(), true);
            const char* glsl_version = "#version 460";
            ImGui_ImplOpenGL3_Init(glsl_version);
            bool show_demo_window = true;
            bool show_another_window = false;
            ImVec4 clear_color = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

            InputHandler::GetInputHandlerInstance(window->getWindowRef());

            float deltaTime = 0.0f;	// Time between current frame and last frame
            float lastFrame = 0.0f; // Time of last frame

            /* Loop until the user closes the window */
            while (!window->getWindowShouldClose())
            {
                float currentFrame = (float)glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGui::ShowDemoWindow(&show_demo_window);
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
                
                window->processInput();

                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(window->getWindowRef(), &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
                //glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                window->swapBuffers();


                glfwPollEvents();
            }
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwTerminate();
        return 0;
    }

   
    

   

}

