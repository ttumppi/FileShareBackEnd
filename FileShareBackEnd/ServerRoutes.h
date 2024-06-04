#include <string>
#include <cpr/cpr.h>
#include <crow_all.h>
#include <json.h>
#include <CurrentUserManagement.h>

#ifndef SERVER_ROUTES_H
#define SERVER_ROUTES_H

class ServerRoutes {
public:

	ServerRoutes(CurrentUserManagement& loggedInUsersManager);

	std::string FetchHomePage();

	std::string FetchDebugPage();

	crow::response FetchCSSFile();

	crow::response FetchScriptFile();

	crow::response ValidateLoginAndRedirect(const crow::request& request, Json::Value users, std::string salt);

private:
	void AddCORSHeaders(crow::response& request);
};

#endif // SERVER_ROUTES_H