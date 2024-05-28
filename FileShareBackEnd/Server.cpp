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
}

void Server::Start() {
    app.port(65000).multithreaded().run();
}

        
    

    

