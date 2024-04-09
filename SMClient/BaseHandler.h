#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

enum MessageType
{
	ADD_EMPLOEE = 1,
	DEL_EPLOEE,
	GET_EMPL_LIST,
	GET_CHIEF,
	SET_POSITION,
	SET_CHIEF
};

class BaseHandler
{
public:
	virtual std::string handle() = 0;
};
