#include "Editor.h"

#include "EngineCore/Engine.h"

#include <iostream>


Editor::Editor()
{
	
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
