#pragma once

#include "core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include "InputHandler.h"

namespace RE {


	class RE_API Window {
	public:
		int m_Width, m_Height;
		const char* m_WindowTitle;
	private:
		GLFWwindow* m_Window;
		
		

	public:
		Window() = delete;
		Window(int width, int height, const char* title);
		~Window();
		
		GLFWwindow* getWindowRef() const;
		bool getWindowShouldClose() const;

		bool initGLAD() const;
		void setInputMode(GLenum mode, GLenum value) const;
		void processInput();
		void swapBuffers();
		
		void setFrameBufferSizeCallBack() const;
		
		


		static void MakeContextCurrent(const Window& window) {
			glfwMakeContextCurrent(window.getWindowRef());
		}
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			GLCall(glViewport(0, 0, width, height));
		}

		static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
		{
			InputHandler::GetInputHandlerInstance(window)->setCursorPos({xpos, ypos});
		}
	};
}


