#pragma once

#include "IWindow.h"
#include "glad/glad.h"
#include "SDL3/SDL.h"

namespace FE {

	class FE_API WindowOGL : public IWindow
	{
	public:

		WindowOGL();

		FEbool Init(int width, int height, const char* title, FEWindowMode windowMode) override;

		void clearBuffer(float r, float g, float b, float a) override;

		void swapBuffer() override;

		~WindowOGL() override;

	private:

		SDL_GLContext m_GLContext;
		GLbitfield m_RendererFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;



	
	};

	
}

