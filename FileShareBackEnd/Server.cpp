#include <crow_all.h>
#include <ServerRoutes.h>
#include <Server.h>
#include <json.h>
#include <CurrentUserManagement.h>

Server::Server(Json::Value users, std::string salt, CurrentUserManagement& sessionManagement) : routes(sessionManagement), _tokenMiddleware(sessionManagement),
    app(_tokenMiddleware){

    _users = users;
    _salt = salt;
    _sessionManagement = sessionManagement;
    

    CROW_ROUTE(app, "/")([this]() {
        return routes.FetchHomePage();
        });

    CROW_ROUTE(app, "/debug")([this]() {
        return routes.FetchDebugPage();
        });

    CROW_ROUTE(app, "/css")([this]() {
        return routes.FetchCSSFile();
        });

    CROW_ROUTE(app, "/script")([this]() {
        return routes.FetchScriptFile();
        });

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        return routes.ValidateLoginAndRedirect(req, _users, _salt);
        });

    CROW_ROUTE(app, "/login/successfull")([this]() {
        return "successfull";
        });

    CROW_ROUTE(app, "/login/failed")([this]() {
        return "failed";
        });

    

}

void Server::Start() {
    app.port(65000).multithreaded().run();
}

        
    

    

