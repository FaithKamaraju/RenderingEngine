#pragma once

#include "EngineMacros.h"
#include "IWindow.h"

namespace FE {
	class WindowD3D11 : public IWindow
	{
	public:
		virtual ~WindowD3D11() override;

		virtual FEbool Init(int width, int height, const char* title, FEWindowMode windowMode) override;

		virtual void clearBuffer(float r, float g, float b, float a) override;

		virtual void swapBuffer() override;
	};
}


