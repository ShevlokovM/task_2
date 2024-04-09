
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "sqlite3.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <memory>
#include <variant>
#include <exception>


#pragma comment(lib, "sqlite3.lib")

enum Types
{
	INTEGER,
	STRNG
};


class DBHandler
{

public:

	DBHandler();
		
	void insertDB(std::string sql);
	void selectDB(std::string sql, std::vector<std::variant<int, std::string> >& external_results, std::vector<int> types);
	void updateDB(std::string sql);
	void deleteDB(std::string sql);	

private:
	sqlite3* db;
	
	void connectDB();
	void closeDB();
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};

