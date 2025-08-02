#pragma once

#include "core/core.h"

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "InputHandler.h"
#include "core/Object.h"


namespace RE {
	class RE_API Camera : public Object
	{
	public:
		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraUp;
		glm::mat4 m_view;
		glm::mat4 m_projection;

		
		
	private:

		float m_cameraMoveSpeed;

		float m_lastX, m_lastY;
		bool m_bFirstMouse = false;

		std::shared_ptr<Window> m_windowRef;

	public:
		Camera(std::shared_ptr<Window> window, float FOV);
		Camera() = delete;
		~Camera();

		void tick(float deltaTime) override;
		void processInput(float deltaTime) override;
		void cameraLook(double xpos, double ypos);
		void scrollCameraMoveSpeed(double xOffset, double yOffset);
		

	};
}


