#include <string>
#include <cpr/cpr.h>
#include <crow_all.h>
#include <json.h>
#include <CurrentUserManagement.h>
#include <RandomToken.h>

#ifndef SERVER_ROUTES_H
#define SERVER_ROUTES_H

class ServerRoutes {
public:

	ServerRoutes(CurrentUserManagement& sessionManagement);

	std::string FetchHomePage();

	std::string FetchDebugPage();

	crow::response FetchCSSFile();

	crow::response FetchScriptFile();

	crow::response ValidateLoginAndRedirect(const crow::request& request, Json::Value users, std::string salt);

	crow::response GatherFile(const crow::request& request, std::string& fileName);

private:
	void AddCORSHeaders(crow::response& request);
	CurrentUserManagement& _sessionManagement;
	RandomToken _tokenGenerator;
};

#endif // SERVER_ROUTES_H