#pragma once

#include "core.h"
#include "Object.h"
#include <mutex>
#include <functional>
#include <vector>
#include "GLFW/glfw3.h"

namespace RE {

	struct RE_API MouseCursorPos {

		double m_MouseCursor_X;
		double m_MouseCursor_y;
	};

	typedef std::function<void()> func;
	typedef std::function<void(const MouseCursorPos&)> MouseCursorCallback;

	

	class RE_API InputHandler
	{
	public:
		
		InputHandler(InputHandler& other) = delete;
		void operator=(const InputHandler&) = delete;

		static InputHandler* GetInputHandlerInstance(GLFWwindow* windowRef);

		inline void registerMouseCursorCallback(const MouseCursorCallback& funcPtr) {
				m_MouseCallbackRegister.push_back(funcPtr);
		}
		//inline void unregisterCallback(const);

		void setCursorPos(MouseCursorPos cursorPos);

	protected:
		
		GLFWwindow* m_WindowRef;
		MouseCursorPos m_cursorPos;
		std::vector<MouseCursorCallback> m_MouseCallbackRegister;
		
		
	private:
		static InputHandler* _inputHandler;
		static std::mutex _mutex;

		inline InputHandler(GLFWwindow* windowRef) :
			m_WindowRef(windowRef), 
			m_cursorPos(0.0, 0.0){};


	};

	
}



