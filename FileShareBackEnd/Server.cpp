#include <crow_all.h>
#include <ServerRoutes.h>
#include <Server.h>
#include <json.h>
#include <CurrentUserManagement.h>

Server::Server(Json::Value users, std::string salt, CurrentUserManagement& sessionManagement) : _routes(sessionManagement), _tokenMiddleware(sessionManagement, _urlsNeedingToken),
    app(_tokenMiddleware), _sessionManagement(sessionManagement){

    _users = users;
    _salt = salt;
    
    
    

    CROW_ROUTE(app, "/")([this]() {
        return _routes.FetchHomePage();
        });

    CROW_ROUTE(app, "/debug")([this]() {
        return _routes.FetchDebugPage();
        });

    CROW_ROUTE(app, "/css")([this]() {
        return _routes.FetchCSSFile();
        });

    CROW_ROUTE(app, "/script")([this]() {
        return _routes.FetchScriptFile();
        });

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        return _routes.ValidateLoginAndRedirect(req, _users, _salt);
        });

    CROW_ROUTE(app, "/login/successfull")([this]() {
        return "successfull";
        });

    CROW_ROUTE(app, "/login/failed")([this]() {
        return "failed";
        });

    CROW_ROUTE(app, "/homepage")([this]() {
        return _routes.GetAllFiles();
        });

    CROW_ROUTE(app, "/upload").methods("POST"_method)([this](const crow::request& request){
        return _routes.SaveFile(request);
    });

    CROW_ROUTE(app, "/download/<int>").methods("GET"_method)([this](const crow::request& request, crow::response& response, int id) {
        return _routes.GetFileData(id);
        });
    
}

void Server::Start() {
    app.port(65000).multithreaded().run();
}

        
    

    

