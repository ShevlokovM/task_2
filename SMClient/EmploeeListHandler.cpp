#include "EmploeeListHandler.h"

EmploeeListHandler::EmploeeListHandler() {}

std::string EmploeeListHandler::handle()
{	
	int type = GET_EMPL_LIST;
	char * ch = (char*) & type;
	std::string request{ch, sizeof(int)}; 
	
	return request;
}
