#pragma once

#include "FEEngine.h"

#include "ApplicationCore/Window/WindowCommon.h"
#include "ApplicationCore/InputHandler.h"




class Editor : public FE::AppInstance {

public:

	Editor();
	int Run() override;

private:
	std::shared_ptr<FE::Window> m_WindowRef;

};



FE::AppInstance* FE::CreateAppInstance() {

	return new Editor();
}
