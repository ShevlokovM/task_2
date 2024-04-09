#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "BaseHandler.h"
#include "AddEmploeeHandler.h"
#include "DelEmploeeHandler.h"
#include "EmploeeListHandler.h"
#include "GetChiefHandler.h"
#include "SetPositionHandler.h"
#include "SetChiefHandler.h"


class MessageHandler
{
	int curr_type;
public:
	MessageHandler();
	std::string serialize(int type);
	std::string deserialize(char * msg);
};
