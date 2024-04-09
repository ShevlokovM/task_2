#include "SetPositionHandler.h"

SetPositionHandler::SetPositionHandler(){}

std::string SetPositionHandler::handle()
{
	std::string name;
	std::string last_name;
	std::string patronimyc;
	int position;
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
	
	position = input_position();
	
	json["name"] = name;
	json["lastName"] = last_name;
	json["patronimyc"] = patronimyc;
	json["position"] = position;
	
	int type = SET_POSITION;
	char * ch = (char*) & type;
	std::string request{ch, sizeof(int)}; 
	
	return request + json.dump();
}

int SetPositionHandler::input_position()
{
	std::string position = "";
	std::cout << "Possible positions:\n"
			"1. Sales representative\n"
			"2. Manager\n"
			"3. Director\n"
			"4. Owner\n";
			
	std::cout << "Input number of position: ";
	std::getline(std::cin, position);
	
	while(position != "1" && position != "2" && position != "3" && position != "4")
	{
		std::cout << "Wrong input, try again.";
		std::cout << "Possible positions:\n"
			"1. Sales representative\n"
			"2. Manager\n"
			"3. Director\n"
			"4. Owner\n";
	std::cout << "Input number of position: ";
	std::getline(std::cin, position);
	}
	return std::stoi(position);
}




