
#include <iostream>
#include <functional>
#include "Camera.h"

RE::Camera::Camera(std::shared_ptr<Window> window, float FOV)
    :m_windowRef(window), m_cameraFront(0.0f, 0.0f, -1.0f), m_cameraUp(0.0f, 1.0f, 0.0f), m_view(1.0f)
{
    m_cameraMoveSpeed = 1.0f;
    m_lastX = (float)(window->m_Width) / 2.0f;
    m_lastY = (float)(window->m_Height) / 2.0f;
    this->m_projection = glm::perspective(glm::radians(FOV),
        (float)(window->m_Width / window->m_Height), 0.1f, 100.0f);
    setRotation(0.0f, -90.0f, 0.0f);

    MouseCursorCallback cb = [this](const MouseCursorPos& curObj) {
            this->cameraLook(curObj.m_MouseCursor_X, curObj.m_MouseCursor_y);   
        };
    InputHandler::GetInputHandlerInstance(window->getWindowRef())->registerMouseCursorCallback(cb);
    
    ScrollOffsetCallback scb = [this](const MouseScrollOffset& scrollObj) {
        this->scrollCameraMoveSpeed(scrollObj.m_ScrollOffset_X, scrollObj.m_ScrollOffset_y);
        };
    InputHandler::GetInputHandlerInstance(window->getWindowRef())->registerScrollOffsetCallback(scb);

    
}

RE::Camera::~Camera()
{

}

void RE::Camera::tick(float deltaTime)
{
    m_view = glm::lookAt(transform.position, transform.position + m_cameraFront, m_cameraUp);

}

void RE::Camera::processInput(float deltaTime)
{
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_W) == GLFW_PRESS)
            transform.position += m_cameraMoveSpeed * deltaTime * m_cameraFront;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_S) == GLFW_PRESS)
            transform.position -= m_cameraMoveSpeed * deltaTime * m_cameraFront;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_A) == GLFW_PRESS)
            transform.position -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraMoveSpeed * deltaTime;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_D) == GLFW_PRESS)
            transform.position += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraMoveSpeed * deltaTime;

        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_Q) == GLFW_PRESS)
            transform.position -= m_cameraMoveSpeed * deltaTime * m_cameraUp;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_E) == GLFW_PRESS)
            transform.position += m_cameraMoveSpeed * deltaTime * m_cameraUp;
}

void RE::Camera::cameraLook(double xpos, double ypos)
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

    this->rotate(yoffset, xoffset,0.0f);

    if (getTransform().rotation.x > 89.0f)
        setRotation(89.0f, getTransform().rotation.y, getTransform().rotation.z);
    if (getTransform().rotation.x < -89.0f)
        this->setRotation(-89.0f, getTransform().rotation.y, getTransform().rotation.z);

    glm::vec3 direction;
    direction.x = cos(glm::radians(getTransform().rotation.y)) * cos(glm::radians(getTransform().rotation.x));
    direction.y = sin(glm::radians(getTransform().rotation.x));
    direction.z = sin(glm::radians(getTransform().rotation.y)) * cos(glm::radians(getTransform().rotation.x));
    m_cameraFront = glm::normalize(direction);
}

void RE::Camera::scrollCameraMoveSpeed(double xOffset, double yOffset)
{
    m_cameraMoveSpeed = glm::clamp(m_cameraMoveSpeed + (float)yOffset * 0.1f, 0.5f, 5.0f );
    //std::cout << m_cameraMoveSpeed << "\n";
}
