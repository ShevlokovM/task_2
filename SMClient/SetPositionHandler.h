#pragma once

#include "BaseHandler.h"

class SetPositionHandler : public BaseHandler
{
	int input_position();
public:
	SetPositionHandler();
	virtual std::string handle() override;	
};
