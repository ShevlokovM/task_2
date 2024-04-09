#include "GetChiefHandler.h"

GetChiefHandler::GetChiefHandler() {}

std::string GetChiefHandler::handle()
{
	std::string name;
	std::string last_name;
	std::string patronimyc;
	nlohmann::json json;
	
	std::cout << "\n------------------------------------\n";
	std::cout << "Input emploee name: ";
	std::getline(std::cin, name);

	std::cout << "\n------------------------------------\n";
	std::cout << "Input emploee last name: ";
	std::getline(std::cin, last_name);
	
	std::cout << "\n------------------------------------\n";
	std::cout << "Input emploee patronimyc: ";
	std::getline(std::cin, patronimyc);
	
	json["name"] = name;
	json["lastName"] = last_name;
	json["patronimyc"] = patronimyc;
	
	int type = GET_CHIEF;
	char * ch = (char*) & type;
	std::string request{ch, sizeof(int)}; 
	
	return request + json.dump();
}
