#include <crow_all.h>
#include <ServerRoutes.h>
#include <Server.h>

Server::Server() {
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
        return "toimii";
        });
}

void Server::Start() {
    app.port(65000).multithreaded().run();
}

        
    

    

