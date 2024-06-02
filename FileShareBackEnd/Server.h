#include <ServerRoutes.h>
#include <crow_all.h>
#include <json.h>


#ifndef SERVER_H
#define SERVER_H

class Server {
public:

	Server(Json::Value users, std::string salt);
	void Start();

private:

	crow::SimpleApp app;
	ServerRoutes routes;

	std::string _salt;
	Json::Value _users;

	
};


#endif // SERVER_H
