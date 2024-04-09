#pragma once

#include "BaseHandler.h"

class DelEmploeeHandler : public BaseHandler
{

public:
	DelEmploeeHandler();
	virtual std::string handle() override;
};
