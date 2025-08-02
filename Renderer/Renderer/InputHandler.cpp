#include "InputHandler.h"

RE::InputHandler* RE::InputHandler::_inputHandler{ nullptr };
std::mutex RE::InputHandler::_mutex;

void RE::InputHandler::setCursorPos(const MouseCursorPos& cursorPos)
{
	this->m_cursorPos = cursorPos;
	for (auto callback : m_MouseCallbackRegister)
	{
		callback(this->m_cursorPos);
	}

}
void RE::InputHandler::setScrollOffset(const MouseScrollOffset& scrollOffset)
{
	this->m_scrollOffset = scrollOffset;
	for (auto callback : m_ScrollOffsetRegister) {
		callback(this->m_scrollOffset);
	}
}

RE::InputHandler* RE::InputHandler::GetInputHandlerInstance(GLFWwindow* windowRef)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_inputHandler == nullptr) {
		_inputHandler = new InputHandler(windowRef);
	}
	return _inputHandler;
}