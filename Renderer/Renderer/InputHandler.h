#pragma once

#include "core/core.h"
#include "core/Object.h"
#include <mutex>
#include <functional>
#include <vector>
#include "GLFW/glfw3.h"

namespace RE {

	struct RE_API MouseCursorPos {

		double m_MouseCursor_X;
		double m_MouseCursor_y;
	};

	struct RE_API MouseScrollOffset {
		double m_ScrollOffset_X;
		double m_ScrollOffset_y;
	};

	typedef std::function<void()> func;
	typedef std::function<void(const MouseCursorPos&)> MouseCursorCallback;
	typedef std::function<void(const MouseScrollOffset&)> ScrollOffsetCallback;

	

	class RE_API InputHandler
	{
	public:
		
		InputHandler(InputHandler& other) = delete;
		void operator=(const InputHandler&) = delete;

		static InputHandler* GetInputHandlerInstance(GLFWwindow* windowRef);

		inline void registerMouseCursorCallback(const MouseCursorCallback& funcPtr) {
				m_MouseCallbackRegister.push_back(funcPtr);
		}
		inline void registerScrollOffsetCallback(const ScrollOffsetCallback& funcPtr) {
				m_ScrollOffsetRegister.push_back(funcPtr);
		}

		void setCursorPos(const MouseCursorPos& cursorPos);
		void setScrollOffset(const MouseScrollOffset& scrollOffset);

	protected:
		
		GLFWwindow* m_WindowRef;
		MouseCursorPos m_cursorPos;
		MouseScrollOffset m_scrollOffset;

		std::vector<MouseCursorCallback> m_MouseCallbackRegister;
		std::vector<ScrollOffsetCallback> m_ScrollOffsetRegister;
		
		
	private:
		static InputHandler* _inputHandler;
		static std::mutex _mutex;

		inline InputHandler(GLFWwindow* windowRef) :
			m_WindowRef(windowRef), 
			m_cursorPos(0.0, 0.0){};


	};

	
}



