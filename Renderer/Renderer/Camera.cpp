
#include "Window.h"
#include "Camera.h"

RE::Camera::Camera(std::shared_ptr<Window> window, float FOV)
    :m_windowRef(window), m_cameraFront(0.0f, 0.0f, -1.0f), m_cameraUp(0.0f, 1.0f, 0.0f), m_view(1.0f)
{
    this->m_projection = glm::perspective(glm::radians(FOV),
        (float)(window->m_Width / window->m_Height), 0.1f, 100.0f);
}

RE::Camera::~Camera()
{

}

void RE::Camera::tick(float deltaTime)
{
    m_view = glm::lookAt(transform.translation, transform.translation + m_cameraFront, m_cameraUp);
}

void RE::Camera::processInput(float deltaTime)
{
    const float cameraSpeed = 1.0f * deltaTime; // adjust accordingly
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_W) == GLFW_PRESS)
            transform.translation += cameraSpeed * m_cameraFront;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_S) == GLFW_PRESS)
            transform.translation -= cameraSpeed * m_cameraFront;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_A) == GLFW_PRESS)
            transform.translation -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
        if (glfwGetKey(m_windowRef->getWindowRef(), GLFW_KEY_D) == GLFW_PRESS)
            transform.translation += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
}
