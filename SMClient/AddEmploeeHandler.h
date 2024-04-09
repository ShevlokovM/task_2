#pragma once

#include "BaseHandler.h"

class AddEmploeeHandler : public BaseHandler
{

public:
	AddEmploeeHandler();
	virtual std::string handle() override;
};

