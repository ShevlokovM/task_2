#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include <nlohmann/json.hpp>

#include "DBHandler.h"

enum MessageType
{
	ADD_EMPLOEE = 1,
	DEL_EPLOEE,
	GET_EMPL_LIST,
	GET_CHIEF,
	SET_POSITION,
	SET_CHIEF
};

class MessageHandler
{
	std::string add_emploee(char * msg);
	std::string delete_emploee(char * msg);
	std::string get_list();
	std::string get_chief(char * msg);
	std::string set_position(char * msg);
	std::string set_chief(char * msg);
	int check_emploee(std::string name, std::string lastName, std::string patronimyc);
	
	std::unique_ptr<DBHandler> db_handler;
	
public:
	MessageHandler();
	std::string handle(char * msg);
};
