#include "MessageHandler.h"

MessageHandler::MessageHandler() {}



std::string MessageHandler::serialize(int type)
{
	curr_type = type;
	std::shared_ptr<BaseHandler> handler;
	
	switch(type)
	{
	case ADD_EMPLOEE:
		handler = std::make_shared<AddEmploeeHandler>();
		break;
	case DEL_EPLOEE:
		handler = std::make_shared<DelEmploeeHandler>();
		break;
	case GET_EMPL_LIST:
		handler = std::make_shared<EmploeeListHandler>();
		break;
	case GET_CHIEF:
		handler = std::make_shared<GetChiefHandler>();
		break;
	case SET_POSITION:
		handler = std::make_shared<SetPositionHandler>();
		break;
	case SET_CHIEF:
		handler = std::make_shared<SetChiefHandler>();
		break;	
	}
	
	return handler->handle();
}

std::string MessageHandler::deserialize(char * msg_)
{
	nlohmann::json json; 
	std::string result_msg;
	std::string msg = "";
	msg.append(msg_);
	
	switch(curr_type)
	{
	case ADD_EMPLOEE:		
	case DEL_EPLOEE:
	case SET_POSITION:		
	case SET_CHIEF:
		result_msg = msg;
		break;
	case GET_EMPL_LIST:
		json = nlohmann::json::parse(msg);
		if(json.contains("error"))
		{
			result_msg += json["error"];
		}
		else
		{
			result_msg += "#\tname\tlast name\tpatronimyc\n";			
			for(auto & row : json)
			{
				int id = row["id"];
				std::string name = row["name"];
				std::string lastName = row["lastName"];
				std::string patronimyc = row["patronimyc"];
				
				result_msg += std::to_string(id) + "\t" 
					+ name + "\t" 
					+ lastName + "\t" 
					+ patronimyc + "\n";
			} 
		}
		break;
	case GET_CHIEF:
		json = nlohmann::json::parse(msg);
		if(json.contains("error"))
		{
			result_msg += json["error"];
		}
		else
		{
			std::string name = json["name"];
			std::string lastName = json["lastName"];
			std::string patronimyc = json["patronimyc"];
			std::string position = json["position"];
			
				
			result_msg = "Position: " + position + "\nChief: " 
				+ lastName + " "
				+ name + " "
				+ patronimyc; 
		}
		break;			
	}
	
	return result_msg;
}
