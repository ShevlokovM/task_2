#include "DBHandler.h"

DBHandler::DBHandler() : db(nullptr) {}

void DBHandler::connectDB()
{
    char* zErrMsg = 0;
    int rc;

    try
    {
        rc = sqlite3_open("../staff", &db);
    }
    catch (const std::exception& e)
    {
        //std::cerr << "Caught exception: " << e.what() << "\n";
    }

    if (rc)
    {  
        std::string err = "Can't open database: ";
        err.append(sqlite3_errmsg(db));        
        throw std::logic_error(err);
    }
    else 
    {        
        //fprintf(stderr, "Opened database successfully\n");
    }     
}

void DBHandler::insertDB(std::string sql)
{
    
    connectDB();

    setlocale(LC_ALL, "rus");
    
    char* zErrMsg = 0;
    int rc;   

        /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) 
    {
        std::string err = "insertDB. SQL error: ";
        err.append(zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);  
        throw std::logic_error(err);        
    }
    
    closeDB();
    
}

void DBHandler::selectDB(std::string sql, std::vector<std::variant<int, std::string> >& external_results, std::vector<int> types)
{    
    
    connectDB();

    sqlite3_stmt* stmt = NULL;    //  stmt statement handle

    //Preparation before query-check the validity of the statement
    //-1 means the system will automatically calculate the length of the SQL statement
    int result;

    try
    {
        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    }
    catch (const std::exception& e)
    {
    	std::string er = "SelectDB. Error: ";
        const char* err = sqlite3_errmsg(db); 
        er.append(err);       
        sqlite3_finalize(stmt);
        closeDB();        
        throw std::logic_error(er);
    }

    std::string str;

    if (result == SQLITE_OK)
    {        
        try
        {            
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                for (int i = 0; i < types.size(); i++)
                {
                    switch (types[i])
                    {
                    case INTEGER:
                        external_results.push_back(sqlite3_column_int(stmt, i));
                        break;
                    case STRNG:
                        str = (char*)sqlite3_column_text(stmt, i);
                        external_results.push_back(str);
                        break;                    
                    //default:
                        //std::cout << "There isn't type like this one!\n";
                    }
                }
            }
        }
        catch (const std::exception& e)
        {            
            std::string er = "SelectDB. Error: ";
            er.append(e.what());            
            sqlite3_finalize(stmt);
            closeDB();
            throw std::logic_error(er);
        }
    }
    else
    {
        const char* err = sqlite3_errmsg(db);
        std::string er = "SelectDB. Error: ";
        er.append(err);
        sqlite3_finalize(stmt);
        closeDB();
        throw std::logic_error(er);
    }

    //Clean up the statement handle and prepare to execute the next statement
    sqlite3_finalize(stmt);  
       
    closeDB();    
}

void DBHandler::updateDB(std::string sql)
{       
    connectDB();

    char* zErrMsg = 0;
    int rc;
    //char* sql;
    const char* data = "Callback function called";
        
        /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) 
    {
        std::string err = "UpdateDB. SQL error: ";
        err.append(zErrMsg);      
        sqlite3_free(zErrMsg);
        sqlite3_close(db);          
        throw std::logic_error(err);
    }
        
    closeDB(); 
}

void DBHandler::deleteDB(std::string sql)
{  
    connectDB();

    char* zErrMsg = 0;
    int rc;
    //char* sql;
    const char* data = "Callback function was called";

    rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        std::string err = "DeleteDB. SQL error: ";
        err.append(zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        throw std::logic_error(err);
    }

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) 
    {
        std::string err = "DeleteDB. SQL error: ";
        err.append(zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        throw std::logic_error(err);
    } 

    //fprintf(stdout, "DELETE was done successfully\n");
    closeDB(); 
}

void DBHandler::closeDB()
{
    int res = sqlite3_close(db);

    if (res != SQLITE_OK)
    {   
        const char* err_msg = sqlite3_errmsg(db);
        std::string err = "Can't close database: ";
        err.append(err_msg);
        throw std::logic_error(err);        
    }
    else
    {
        //fprintf(stdout, "DB closing was done successfully\n");
    }
}

int DBHandler::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    int i;
    for (i = 0; i < argc; i++) 
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    //printf("\n");
    return 0;
}

