#include <iostream>
#include <memory>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "MessageHandler.h"

using namespace std;

int get_request_type()
{    
	std::cout << "Possible request types:\n"
			"1. Add emploee\n"
			"2. Delete emploee\n"
			"3. Get employees list\n"
			"4. Get position and chief of emploee\n"
			"5. Set emploee position\n"
			"6. Set emploee chief\n";
	std::cout << "Input number of request: ";    
    std::string type = "";    
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    int n = 0;
    while(!std::cin.eof())
    {
        std::cin.ignore();
        std::cout << ++n << "\n";
    }
    //std::cin.clear();
    //std::cin.ignore(200);
	std::getline(std::cin, type);
	
	while(type != "1" && type != "2" && type != "3" && type != "4" && type != "5" && type != "6")
	{
		std::cout << "Wrong input, try again.";
		std::cout << "Possible request types:\n"
			"1. Add emploee\n"
			"2. Delete emploee\n"
			"3. Get employees list\n"
			"4. Get position and chief of emploee\n"
			"5. Set emploee position\n"
			"6. Set emploee chief\n";
	std::cout << "Input number of request: ";
    type = "";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max());
	std::getline(std::cin, type);
	}
	return std::stoi(type);
}

int main()
{
    std::unique_ptr<MessageHandler> message_handler = std::make_unique<MessageHandler>();
    	
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    string userInput;

    do 
    {
        int request_type = get_request_type();        
        std::string input = message_handler->serialize(request_type);

        //		Send to server
        int sendRes = send(sock, input.c_str(), input.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            char * msg = new char[bytesReceived];
	    strncpy(msg, buf, bytesReceived);
            cout << "SERVER> " << message_handler->deserialize(msg) << "\r\n";
            delete[] msg;
        }
    } while(true);

    //	Close the socket
    close(sock);

    return 0;
}
