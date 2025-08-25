#include "WindowOGL.h"

#include <iostream>
#include "glad/glad.h"
#include "EngineCore/GameplayStatics/EngineStatics.h"
#include "EngineCore/InputSubsystem/InputHandler.h"

FE::WindowOGL::WindowOGL()
{
}

FEbool FE::WindowOGL::Init(int width, int height, const char* title, FEWindowMode windowMode)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;
	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return FE_FAILED;
	}
	unsigned int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;

	if (windowMode & FE_WINDOW_FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN;
	else if (windowMode & FE_WINDOW_BORDERLESS_WINDOWED)
		flags |= SDL_WINDOW_BORDERLESS;

	if (windowMode & FE_WINDOW_MINIMIZED)
		flags |= SDL_WINDOW_MINIMIZED;
	else if (windowMode & FE_WINDOW_MAXIMIZED)
		flags |= SDL_WINDOW_MAXIMIZED;

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		
	//Create window
	m_Window = SDL_CreateWindow(title, width, height, flags);
	if (m_Window == NULL)
	{
		SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return FE_FAILED;
	}
		//Create context
	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (m_GLContext == NULL)
	{
		SDL_Log("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return FE_FAILED;
	}

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return FE_FAILED;
	}

	//Use Vsync
	SDL_GL_SetSwapInterval(1);

	GetInputHandler()->RegisterListener(
		[this](const FE::InputEvent& event, float deltaTime) {
			processInput(event, deltaTime);
		});

    return FE_SUCCESS;
}


void FE::WindowOGL::clearBuffer(float r, float g, float b, float a)
{
    
    GLCall(glClearColor(1.f, 0.f, 1.f, 0.f));
    GLCall(glClear(m_RendererFlags));
}

void FE::WindowOGL::swapBuffer()
{
    SDL_GL_SwapWindow(m_Window);
}


FE::WindowOGL::~WindowOGL()
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}