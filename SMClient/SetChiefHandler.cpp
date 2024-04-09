#include "SetChiefHandler.h"

SetChiefHandler::SetChiefHandler() {}

std::string SetChiefHandler::handle()
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
	
	json["emploee"]["name"] = name;
	json["emploee"]["lastName"] = last_name;
	json["emploee"]["patronimyc"] = patronimyc;	
	
	
	std::cout << "\n------------------------------------\n";
	std::cout << "Input chief name: ";
	std::getline(std::cin, name);

	std::cout << "\n------------------------------------\n";
	std::cout << "Input chief last name: ";
	std::getline(std::cin, last_name);
	
	std::cout << "\n------------------------------------\n";
	std::cout << "Input chief patronimyc: ";
	std::getline(std::cin, patronimyc);
	
	json["chief"]["name"] = name;
	json["chief"]["lastName"] = last_name;
	json["chief"]["patronimyc"] = patronimyc;	
	
	int type = SET_CHIEF;
	char * ch = (char*) & type;
	std::string request{ch, sizeof(int)}; 
	
	return request + json.dump();
}
