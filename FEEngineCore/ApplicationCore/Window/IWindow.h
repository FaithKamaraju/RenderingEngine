#pragma once

#include "EngineMacros.h"
#include "Symbols.h"
#include <memory>
struct SDL_Window;
namespace FE {

	struct InputEvent;
	class FE_API IWindow {
		
	protected:

		
		bool bShouldWindowClose = false;

	public:
		SDL_Window* m_Window;
		int m_Width, m_Height;
		const char* m_Title;

		IWindow();

		virtual ~IWindow() = default;

		virtual FEbool Init(int width, int height, const char* title, FEWindowMode windowMode) = 0;

		virtual void clearBuffer(float r, float g, float b, float a) = 0;

		virtual void swapBuffer() = 0;

		inline bool getWindowShouldClose() const { return bShouldWindowClose; };

		inline void setWindowShouldClose(bool value) { bShouldWindowClose = value; };

		void setCursorMode(FECursorMode mode) const;

		virtual void processInput(const InputEvent& event, float deltaTime);

		static std::shared_ptr<IWindow> CreateWindowObj(GraphicsAPI api);
	};
}


