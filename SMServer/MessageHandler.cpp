#include "MessageHandler.h"

MessageHandler::MessageHandler() 
{
	db_handler = std::make_unique<DBHandler>();
}

std::string MessageHandler::handle(char * msg)
{
	int type = *((int*) msg);
	msg += sizeof(int);
	
	try
	{
		switch(type)
		{
		case ADD_EMPLOEE:
			return add_emploee(msg);
		case DEL_EPLOEE:
			return delete_emploee(msg);
		case GET_EMPL_LIST:
			return get_list();
        case GET_CHIEF:
			return get_chief(msg);
		case SET_POSITION:
			return set_position(msg);
        case SET_CHIEF:
			return set_chief(msg);
		default:
			return "Wrong request type";
		}
	}
	catch (const std::exception & e)
	{
		std::string err = "Caught exception: ";
		err.append(err);
		return err; 
	}	
}

std::string MessageHandler::add_emploee(char * msg)
{
	std::string msg_ = "";
	msg_.append(msg);
	
	nlohmann::json json = nlohmann::json::parse(msg_);	
	
	
	std::string sql = "INSERT INTO employees (name, lastName, patronimyc) VALUES ('"
		+ (std::string) json["name"] + "', '" + (std::string) json["lastName"] + "', '" 
		+ (std::string) json["patronimyc"] + "'"; 
		
	try
	{
		db_handler->insertDB(sql);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught excsption: " << e.what() << "\n";
		return "Request failed!";
	}
	
	return "New emploee successfully added to database!";
}

std::string MessageHandler::delete_emploee(char * msg)
{
	std::string msg_ = "";
	msg_.append(msg);
	
	nlohmann::json json = nlohmann::json::parse(msg_);
	
	int id;
	
	try
	{
		id = check_emploee(json["name"], json["lastName"], json["patronimyc"]);
	}
	catch (const std::exception & e)
	{
		std::string err = "";
		err.append(e.what());
		return err;
	}
			
	if(id == -1)
		return "There isn't sauch emploee!";	
	
	std::string sql = "DELETE FROM employees WHERE id = '" + std::to_string(id);		
			
	try
	{
		db_handler->deleteDB(sql);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught excsption: " << e.what() << "\n";
		return "Request failed!";
	}
	
	return "New emploee successfully deleted from database!";
}


std::string MessageHandler::get_list()
{	
	std::string sql = "SELECT * FROM employees";
	std::vector<std::variant<int, std::string> > result;
	std::vector<int> types = { INTEGER, STRNG, STRNG, STRNG };
	
	try
	{
		db_handler->selectDB(sql, result, types);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught excsption: " << e.what() << "\n";
		return "{ \"error\": \"Request failed!\" }";
	}
	
	nlohmann::json answer;
	
	for(int i = 0; i < result.size(); i++)
	{
		nlohmann::json row;
		row["id"] = std::get<int>(result[i]);
		i++;
		row["name"] = std::get<std::string>(result[i]);
		i++;
		row["lastName"] = std::get<std::string>(result[i]);
		i++;
		row["patronimyc"] = std::get<std::string>(result[i]);
		
		answer.push_back(row);
	}
	
	std::string answer_ = answer.dump();
	return answer;
}


std::string MessageHandler::get_chief(char * msg)
{
	std::string msg_ = "";
	msg_.append(msg);
	
	nlohmann::json json = nlohmann::json::parse(msg_);
	
	int id;
	int cheef_id;
	
	try
	{
		id = check_emploee(json["name"], json["lastName"], json["patronimyc"]);
	}
	catch (const std::exception & e)
	{
		std::string err = "";
		err.append(e.what());
		return err;
	}
			
	if(id == -1)
		return "Wrong emploee name!";
		
		
	std::string sql = "SELECT employees.name, employees.lastName, employees.patronimyc "
		"FROM employees WHERE employees.id = "
		"("
			"SELECT structure.chiefId FROM structure "
			"WHERE structure.emploeeId = " + std::to_string(id) + 
		")";
	
	std::vector<std::variant<int, std::string> > result;
	std::vector<int> types = { STRNG, STRNG, STRNG };
	
	try
	{
		db_handler->selectDB(sql, result, types);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught excsption: " << e.what() << "\n";
		return "{ \"error\": \"Request failed!\" }";
	}
	
	nlohmann::json answer;
	
	for(int i = 0; i < result.size(); i++)
	{
		nlohmann::json row;
		
		answer["name"] = std::get<std::string>(result[i]);
		i++;
		answer["lastName"] = std::get<std::string>(result[i]);
		i++;
		answer["patronimyc"] = std::get<std::string>(result[i]);
	}
	
	sql = "SELECT positions.positionName FROM positions "
		"JOIN employees ON positions.id = employees.position "
		"WHERE id = " + std::to_string(id);
	result.clear();
	types = { STRNG };	
	
	try
	{
		db_handler->selectDB(sql, result, types);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught excsption: " << e.what() << "\n";
		return "{ \"error\": \"Request failed!\" }";
	}
	
	if(result.size() == 0) 
		return "{ \"error\": \"Request failed!\" }";
		
	answer["position"] = std::get<std::string>(result[0]);	
		
	std::string answer_ = answer.dump();
	return answer; 
}


std::string MessageHandler::set_position(char * msg)
{
	std::string msg_ = "";
	msg_.append(msg);
	
	nlohmann::json json = nlohmann::json::parse(msg_);
	
	int id;
	
	try
	{
		id = check_emploee(json["name"], json["lastName"], json["patronimyc"]);
		
	}
	catch (const std::exception & e)
	{
		std::string err = "";
		err.append(e.what());
		return err;
	}
			
	if(id == -1)
		return "Wrong emploee name!";
		
	std::string sql = "UPDATE employees SET position = "
		+ std::to_string((int) json["position"]) 
		+ "WHERE id = " + std::to_string(id);
		
	try
	{
		db_handler->updateDB(sql);
	}
	catch (const std::exception & e)
	{
		std::cout << "Caught exception: " << e.what();
		return "Request failed!";
	}
	
	return "Success!";
}


std::string MessageHandler::set_chief(char * msg)
{
	std::string msg_ = "";
	msg_.append(msg);
	
	nlohmann::json json = nlohmann::json::parse(msg_);
	
	int id;
	int cheef_id;
	
	try
	{
		id = check_emploee(json["emploee"]["name"], 
			json["emploee"]["lastName"], json["emploee"]["patronimyc"]);
		cheef_id = check_emploee(json["chief"]["name"], 
			json["chief"]["lastName"], json["chief"]["patronimyc"]);
	}
	catch (const std::exception & e)
	{
		std::string err = "";
		err.append(e.what());
		return err;
	}
			
	if(id == -1)
		return "Wrong emploee name!";
		
	if(cheef_id == -1)
		return "Wrong cheef name!";	
		
	std::string sql = "INSERT INTO structure (emploeeId, chiefId) VALUES ("
		+ std::to_string(id) + ", " + std::to_string(cheef_id) + ")";
		
	try
	{
		db_handler->insertDB(sql);
	}
	catch (const std::exception & e)
	{
		std::cout << "Caught exception: " << e.what();
		return "Request failed!";
	}
	
	return "Success!";
}

int MessageHandler::check_emploee(std::string name, std::string lastName, std::string patronimyc)
{
	std::string sql = "SELECT id FROM employees WHERE name = '" 
		+ name + "' AND lastName = '"
		+ lastName + "' AND patronimyc = '"
		+ patronimyc + "'";
		
	std::vector<std::variant<int,std::string>> result;
	std::vector<int> types = { INTEGER };
	
	try
	{
		db_handler->selectDB(sql, result, types);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Caught excsption: " << e.what() << "\n";
		throw std::logic_error("Request failed!");
	}
	
	if(result.size() > 0) 
		return std::get<int>(result[0]);
	else 
		return -1;	
}








