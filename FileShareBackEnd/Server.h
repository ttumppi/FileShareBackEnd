#include <ServerRoutes.h>
#include <crow_all.h>
#include <json.h>
#include <CurrentUserManagement.h>
#include <TokenMiddleware.h>

#ifndef SERVER_H
#define SERVER_H

class Server {
public:

	Server(Json::Value users, std::string salt, CurrentUserManagement& sessionManagement);
	void Start();

private:

	
	ServerRoutes routes;
	TokenMiddleware _tokenMiddleware;
	crow::App<TokenMiddleware> app;
	std::string _salt;
	Json::Value _users;
	CurrentUserManagement _sessionManagement;
	
	
};


#endif // SERVER_H
