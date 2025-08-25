#include "IWindow.h"
#include <stdexcept>
#include "WindowOGL.h"
#include "WindowD3D11.h"
#include "EngineCore/InputSubsystem/InputHandler.h"
#include "SDL3/SDL.h"





std::shared_ptr<FE::IWindow> FE::IWindow::CreateWindowObj(GraphicsAPI api)
{
	switch (api)
	{
	case GraphicsAPI::OPENGL:
		return std::make_shared<WindowOGL>();
	case GraphicsAPI::D3D11:
		return std::make_shared<WindowD3D11>();
	/*case GraphicsAPI::VULKAN:
		return std::make_unique<VulkanWindow>();*/
	default:
		throw std::runtime_error("Unknown graphics API");
	}
}

FE::IWindow::IWindow()
{
	
}

void FE::IWindow::setCursorMode(FECursorMode mode) const
{
	switch (mode) {

	case FE_CURSOR_VISIBLE:
		SDL_SetWindowRelativeMouseMode(m_Window, false);
		SDL_CaptureMouse(false);
		SDL_SetWindowMouseGrab(m_Window, false);
		SDL_ShowCursor();
		break;

	case FE_CURSOR_HIDDEN:
		SDL_SetWindowRelativeMouseMode(m_Window, false);
		SDL_CaptureMouse(false);
		SDL_SetWindowMouseGrab(m_Window, false);
		SDL_HideCursor();
		break;

	case FE_CURSOR_RELATIVE:
		SDL_SetWindowRelativeMouseMode(m_Window,true);
		SDL_CaptureMouse(false);
		SDL_SetWindowMouseGrab(m_Window, false);
		break;

	case FE_CURSOR_GRABBED:
		SDL_SetWindowRelativeMouseMode(m_Window, false);
		SDL_CaptureMouse(false);
		SDL_SetWindowMouseGrab(m_Window,true);
		break;

	case FE_CURSOR_CAPTURED:
		SDL_SetWindowRelativeMouseMode(m_Window,false);
		SDL_CaptureMouse(true);
		SDL_SetWindowMouseGrab(m_Window, false);
		break;
	}
}

void FE::IWindow::processInput(const FE::InputEvent& event, float deltaTime) 
{
	if (event.type == FE_EVENT_QUIT || (event.type == FE_EVENT_KEY_UP && event.key.scancode == FE_SCANCODE_ESCAPE))
	{
		bShouldWindowClose = true;
	}
}

