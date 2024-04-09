#pragma once

#include "BaseHandler.h"

class EmploeeListHandler : public BaseHandler
{

public:
	EmploeeListHandler();
	virtual std::string handle() override; 
};
