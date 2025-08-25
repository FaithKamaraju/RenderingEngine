#pragma once

#include "FEEngine.h"


class Editor : public FE::AppInstance {

public:

	Editor();
	int Run() override;

};



FE::AppInstance* FE::CreateAppInstance() {

	return new Editor();
}
