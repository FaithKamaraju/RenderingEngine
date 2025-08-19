#include "Camera.h"

#include <iostream>
#include <functional>
#include "Renderer/Constants.h"
#include "Renderer/OpenGL/ErrorChecking.h"

FE::Camera::Camera(std::shared_ptr<Window> window, float FOV)
    :m_windowRef(window), m_cameraFront(0.0f, 0.0f, -1.0f), m_cameraUp(0.0f, 1.0f, 0.0f), m_view(1.0f)
{
    m_cameraMoveSpeed = 1.0f;
    m_lastX = (float)(window->m_Width) / 2.0f;
    m_lastY = (float)(window->m_Height) / 2.0f;
    this->m_projection = glm::perspective(glm::radians(FOV),
        (float)(window->m_Width / window->m_Height), 0.1f, 100.0f);
    setRotationLocal(0.0f, -90.0f, 0.0f);

    MouseCursorCallback cb = [this](const MouseCursorPos& curObj) {
            this->cameraLook(curObj.m_MouseCursor_X, curObj.m_MouseCursor_y);   
        };
    InputHandler::GetInputHandlerInstance(window->getWindowRef())->registerMouseCursorCallback(cb);
    
    ScrollOffsetCallback scb = [this](const MouseScrollOffset& scrollObj) {
        this->scrollCameraMoveSpeed(scrollObj.m_ScrollOffset_X, scrollObj.m_ScrollOffset_y);
        };
    InputHandler::GetInputHandlerInstance(window->getWindowRef())->registerScrollOffsetCallback(scb);

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

}

void FE::Camera::tick(float deltaTime)
{
    m_view = glm::lookAt(transform.globalPosition, transform.globalPosition + m_cameraFront, m_cameraUp);
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesUBO));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, glm::value_ptr(m_view)));
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 128, 16, glm::value_ptr(transform.globalPosition)));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void FE::Camera::processInput(float deltaTime)
{
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_W) == GLFW_PRESS)
            transform.globalPosition += m_cameraMoveSpeed * deltaTime * m_cameraFront;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_S) == GLFW_PRESS)
            transform.globalPosition -= m_cameraMoveSpeed * deltaTime * m_cameraFront;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_A) == GLFW_PRESS)
            transform.globalPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraMoveSpeed * deltaTime;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_D) == GLFW_PRESS)
            transform.globalPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraMoveSpeed * deltaTime;

        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_Q) == GLFW_PRESS)
            transform.globalPosition -= m_cameraMoveSpeed * deltaTime * m_cameraUp;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_E) == GLFW_PRESS)
            transform.globalPosition += m_cameraMoveSpeed * deltaTime * m_cameraUp;
}

void FE::Camera::cameraLook(double xpos, double ypos)
{
    if (m_bFirstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_bFirstMouse = false;
    }
    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // reversed since y-coordinates range from bottom to top
    m_lastX = xpos;
    m_lastY = ypos;

    const float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    this->rotateLocal(yoffset, xoffset,0.0f);

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

void FE::Camera::scrollCameraMoveSpeed(double xOffset, double yOffset)
{
    m_cameraMoveSpeed = glm::clamp(m_cameraMoveSpeed + (float)yOffset * 0.1f, 0.5f, 5.0f );
    //std::cout << m_cameraMoveSpeed << "\n";
}
