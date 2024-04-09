#pragma once

#include "BaseHandler.h"

class GetChiefHandler : public BaseHandler
{

public:
	GetChiefHandler();
	virtual std::string  handle() override;
};

