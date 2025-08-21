#include "Editor.h"

#include "EngineCore/Engine.h"

#include <iostream>


Editor::Editor()
{
	m_WindowRef = std::make_shared<FE::Window>(1280, 720, "Hello World!");

	m_WindowRef->initGLAD();
	m_WindowRef->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);
	
}

int Editor::Run()
{
	FE::Engine* engineObj = FE::CreateEngineInstance();
	if (!engineObj) {
		std::cerr << "Failed to create renderer." << std::endl;
		return -1;
	}
	int resultInit = engineObj->InitializeEngine();
	int result = engineObj->StartEngineLoop();
	delete engineObj;
	return 0;
}
