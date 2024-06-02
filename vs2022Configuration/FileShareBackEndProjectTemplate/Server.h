#include <ServerRoutes.h>
#include <crow_all.h>

#ifndef SERVER_H
#define SERVER_H

class Server {
public:

	Server();
	void Start();

private:

	crow::SimpleApp app;
	ServerRoutes routes;
};


#endif // SERVER_H
