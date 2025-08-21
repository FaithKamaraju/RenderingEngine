#pragma once

#include "EngineMacros.h"
#include "Symbols.h"


namespace FE {
	 
	class FE_API IWindow {

	public:

		virtual ~IWindow() = 0;

		virtual void Init(int width, int height, const char* title, FEenum windowMode) = 0;
		
		virtual bool getWindowShouldClose() const = 0;

		virtual void setInputMode(FEenum mode, FEenum value) const = 0;

		virtual void processInput() = 0;

		virtual void clearBuffers() = 0;

		virtual void swapBuffers() = 0;

		virtual void setFrameBufferSizeCallBack() const = 0;
		
		static std::unique_ptr<IWindow> CreateWindow();
	};
}


