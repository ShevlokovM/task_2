#pragma once

#include "BaseHandler.h"

class SetChiefHandler : public BaseHandler
{

public:
	SetChiefHandler();
	virtual std::string handle() override;
};
