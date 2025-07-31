#pragma once

#include "core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
		void setFrameBufferSizeCallBack() const;

		void processInput();
		void swapBuffers();


		static void MakeContextCurrent(const Window& window) {
			glfwMakeContextCurrent(window.getWindowRef());
		}
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			GLCall(glViewport(0, 0, width, height));
		}
	};
}


