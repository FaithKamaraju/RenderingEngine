#pragma once

#include "IWindow.h"
#include "ApplicationCore/InputHandler.h"

namespace FE {

	class FE_API WindowOGL : public IWindow
	{

	public:

		~WindowOGL() override;

		void Init(int width, int height, const char* title, FEenum windowMode) override;

		bool getWindowShouldClose() const;

		void setInputMode(FEenum mode, FEenum value) const;

		void processInput();

		void clearBuffers();

		void swapBuffers();

		void setFrameBufferSizeCallBack() const;

		static std::unique_ptr<IWindow> CreateWindow();
	};

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		InputHandler::GetInputHandlerInstance(window)->setCursorPos({ xpos, ypos });
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		InputHandler::GetInputHandlerInstance(window)->setScrollOffset({ xoffset, yoffset });
	}
}


