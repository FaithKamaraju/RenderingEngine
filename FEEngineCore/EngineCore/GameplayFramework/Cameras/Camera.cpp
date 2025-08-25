#include "Camera.h"
#include "glad/glad.h"
#include <iostream>
#include <functional>

#include "Renderer/Constants.h"
#include "EngineCore/GameplayStatics/EngineStatics.h"
#include "EngineCore/InputSubsystem/InputHandler.h"
#include "Renderer/OpenGL/ErrorChecking.h"

FE::Camera::Camera(std::shared_ptr<IWindow> window, float FOV)
    :m_cameraFront(0.0f, 0.0f, -1.0f), m_cameraUp(0.0f, 1.0f, 0.0f), m_view(1.0f)
{
    m_cameraMoveSpeed = 1.0f;
    m_lastX = (float)(window->m_Width) / 2.0f;
    m_lastY = (float)(window->m_Height) / 2.0f;
    this->m_projection = glm::perspective(glm::radians(FOV),
        (float)(window->m_Width / window->m_Height), 0.1f, 100.0f);
    setRotationLocal(0.0f, -90.0f, 0.0f);

    GLCall(glGenBuffers(1, &m_MatricesUBO));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesUBO));
    GLCall(glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 9, NULL, GL_DYNAMIC_DRAW));
    GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, BPI_GlobalCameraMatrices,
        m_MatricesUBO, 0, sizeof(glm::vec4) * 9));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0,   64, glm::value_ptr(m_view)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 64,  64, glm::value_ptr(m_projection)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 128, 16, glm::value_ptr(transform.globalPosition)));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    
}

FE::Camera::~Camera()
{

}

void FE::Camera::beginPlay()
{
    GetInputHandler()->RegisterListener(
        [this](const InputEvent& event, float deltaTime) {
            processInput(event, deltaTime);
        });
}

void FE::Camera::tick(float deltaTime)
{
    m_view = glm::lookAt(transform.globalPosition, transform.globalPosition + m_cameraFront, m_cameraUp);
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesUBO));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, glm::value_ptr(m_view)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 128, 16, glm::value_ptr(transform.globalPosition)));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void FE::Camera::processInput(const InputEvent& event, float deltaTime)
{
    if (event.type == FE_EVENT_MOUSE_MOTION) {
        cameraLook(event.mouseMotion.xRel, event.mouseMotion.yRel);

    }

    if (event.type == FE_EVENT_MOUSE_WHEEL) {
        scrollCameraMoveSpeed(event.mouseWheel.wheelX, event.mouseWheel.wheelY);
    }
    
    if (event.type == FE_EVENT_KEY_DOWN && event.key.scancode == FE_SCANCODE_W)
    {
        transform.globalPosition += m_cameraMoveSpeed * deltaTime * m_cameraFront;

    }
           
    if (event.type == FE_EVENT_KEY_DOWN && event.key.scancode == FE_SCANCODE_S)
    {
        transform.globalPosition -= m_cameraMoveSpeed * deltaTime * m_cameraFront;

    }
        
    if (event.type == FE_EVENT_KEY_DOWN && event.key.scancode == FE_SCANCODE_A)
    {
        transform.globalPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraMoveSpeed * deltaTime;

    }
       
    if (event.type == FE_EVENT_KEY_DOWN && event.key.scancode == FE_SCANCODE_D) 
    {
        transform.globalPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraMoveSpeed * deltaTime;

    }
    
    if (event.type == FE_EVENT_KEY_DOWN && event.key.scancode == FE_SCANCODE_Q)
    {
        transform.globalPosition -= m_cameraMoveSpeed * deltaTime * m_cameraUp;

    }
        
    if (event.type == FE_EVENT_KEY_DOWN && event.key.scancode == FE_SCANCODE_E)
    {
        transform.globalPosition += m_cameraMoveSpeed * deltaTime * m_cameraUp;
    }
        
}

void FE::Camera::cameraLook(float xpos, float ypos)
{
    //if (m_bFirstMouse)
    //{
    //    m_lastX = xpos;
    //    m_lastY = ypos;
    //    m_bFirstMouse = false;
    //}
    //float xoffset = xpos - m_lastX;
    //float yoffset = m_lastY - ypos; // reversed since y-coordinates range from bottom to top
    //m_lastX = xpos;
    //m_lastY = ypos;

    const float sensitivity = 0.05f;
    xpos *= sensitivity;
    ypos *= -1.f * sensitivity;

    this->rotateLocal(ypos, xpos,0.0f);

    if (getTransform().rotation.x > 89.0f)
        setRotationLocal(89.0f, getTransform().rotation.y, getTransform().rotation.z);
    if (getTransform().rotation.x < -89.0f)
        this->setRotationLocal(-89.0f, getTransform().rotation.y, getTransform().rotation.z);

    glm::vec3 direction;
    direction.x = cos(glm::radians(getTransform().rotation.y)) * cos(glm::radians(getTransform().rotation.x));
    direction.y = sin(glm::radians(getTransform().rotation.x));
    direction.z = sin(glm::radians(getTransform().rotation.y)) * cos(glm::radians(getTransform().rotation.x));
    m_cameraFront = glm::normalize(direction);
}

void FE::Camera::scrollCameraMoveSpeed(float xOffset, float yOffset)
{
    m_cameraMoveSpeed = glm::clamp(m_cameraMoveSpeed + yOffset * 0.1f, 0.5f, 5.0f );
    //std::cout << m_cameraMoveSpeed << "\n";
}
