#include <string>
#include <cpr/cpr.h>
#include <crow_all.h>

#ifndef SERVER_ROUTES_H
#define SERVER_ROUTES_H

class ServerRoutes {
public:

	ServerRoutes();

	std::string FetchHomePage();

	std::string FetchDebugPage();

	crow::response FetchCSSFile();

	crow::response FetchScriptFile();
};

#endif // SERVER_ROUTES_H