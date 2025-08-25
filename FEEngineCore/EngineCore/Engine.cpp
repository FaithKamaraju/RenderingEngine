
#include "Engine.h"
#include <iostream>
#include <memory>

#include "EngineCore/InputSubsystem/InputHandler.h"
#include "ApplicationCore/Window/IWindow.h"
#include "EngineCore/GameplayStatics/EngineGlobals.h"

#include "EngineCore/GameplayFramework/Cameras/Camera.h"

#include "SDL3/SDL.h"

#include "Renderer/Constants.h"
#include "EngineCore/GameplayStatics/EngineStatics.h"
#include "Renderer/OpenGL/Shader.h"
#include "Renderer/Mesh/Model.h"
#include "Renderer/Lights/PointLight.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



FE_API FE::Engine* FE::CreateEngineInstance()
{
    Engine* engineObj = new Engine();
    EngineGlobals::engineObj = engineObj;
    return engineObj ;
}
   
int FE::Engine::InitializeEngine()
{
    this->m_AppConfig = LoadConfig("test");
    this->m_InputHandlerInst = std::make_shared<InputHandler>();
    this->m_WindowObj = IWindow::CreateWindowObj(m_AppConfig.api);
    this->m_WindowObj->Init(m_AppConfig.width, m_AppConfig.height, m_AppConfig.title, FE_WINDOW_WINDOWED);
    

    return 0;
}

FE::Config FE::Engine::LoadConfig(const char* configpath)
{
    Config config;
    config.api = GraphicsAPI::OPENGL;
    config.width = 1280;
    config.height = 720;
    config.title = "HelloWorld";
    return config;
}

int FE::Engine::StartEngineLoop()
{

    std::unique_ptr<Camera> camera = std::make_unique<Camera>(this->m_WindowObj, 60.0f);
    camera->translateGlobal(0.0f, 0.0f, 10.0f);
    
    m_WindowObj->setCursorMode(FE_CURSOR_RELATIVE);

    Model model("Resources/Models/Basic/Quad/Quad.obj");


    Shader shader;
    shader.AttachShaders("Resources/Shaders/BasicShader.shader");
    GLCall(unsigned int MatricesBlockIndex = glGetUniformBlockIndex(shader.m_ShaderProgramID, "CameraData"));
    GLCall(glUniformBlockBinding(shader.m_ShaderProgramID, MatricesBlockIndex, BPI_GlobalCameraMatrices));

    GLCall(unsigned int DirLightBlockIndex = glGetUniformBlockIndex(shader.m_ShaderProgramID, "DirectionalLight"));
    GLCall(glUniformBlockBinding(shader.m_ShaderProgramID, DirLightBlockIndex, BPI_DirLight));

    GLCall(unsigned int LightsBlockIndex = glGetUniformBlockIndex(shader.m_ShaderProgramID, "Lights"));
    GLCall(glUniformBlockBinding(shader.m_ShaderProgramID, LightsBlockIndex, BPI_Lights));
    glm::mat4 ModelMT = glm::mat4(1.0f);
    ModelMT = glm::translate(ModelMT, glm::vec3(0.f, -1.f, 0.0f));
    ModelMT = glm::scale(ModelMT, glm::vec3(20.f));
    glm::mat3 NormalMT = glm::mat3(glm::transpose(glm::inverse(ModelMT)));

    /*auto dirLight = std::make_shared<DirectionalLight>();
    dirLight->setPositionGlobal(10.f, 10.f, 10.f);*/

    auto pointLight = std::make_shared<PointLight>();
    pointLight->setPositionGlobal(0.f, 1.f, 0.0f);




    camera->beginPlay();
    pointLight->beginPlay();

    uint64_t deltaTime = 0;	// Time between current frame and last frame
    uint64_t lastFrame = SDL_GetTicks(); // Time of last frame
    
    /* Loop until the user closes the window */
    while (!m_WindowObj->getWindowShouldClose())
    {
        uint64_t currentFrame = SDL_GetTicks();
        float deltaTime = 0.f;
        deltaTime = currentFrame - lastFrame;
        deltaTime /= 1000.f;
        lastFrame = currentFrame;
        
        m_InputHandlerInst->PollEvents(deltaTime);

        camera->tick(deltaTime);

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_CULL_FACE));

        /* Render here */
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader.UseShaderProgram();
        shader.setMatrix4fv("model", 1, false, glm::value_ptr(ModelMT));
        shader.setMatrix3fv("normalMatrix", 1, false, glm::value_ptr(NormalMT));
        model.Draw(shader);

        m_WindowObj->swapBuffer();
        
    }

    return 0;
}
