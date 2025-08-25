#pragma once

#include "EngineMacros.h"
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ApplicationCore/Window/IWindow.h"

#include "EngineCore/GameplayFramework/Object.h"


namespace FE {
	class FE_API Camera : public Object
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
		unsigned int m_MatricesUBO;
		//std::shared_ptr<IWindow> m_windowRef;

	public:
		Camera(std::shared_ptr<IWindow> window, float FOV);
		Camera() = delete;
		~Camera();


		void beginPlay() override;
		void tick(float deltaTime) override;
		void processInput(const InputEvent& event, float deltaTime) override;
		void cameraLook(float xpos, float ypos);
		void scrollCameraMoveSpeed(float xOffset, float yOffset);
		

	};
}


