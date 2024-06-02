#include <cstdio>
#include <string>
#include <crow_all.h>
#include <cpr/cpr.h>
#include <ServerRoutes.h>
#include <json.h>
#include <TurnStringSecure.h>

ServerRoutes::ServerRoutes() {

}

std::string ServerRoutes::FetchHomePage() {
    cpr::Response responseToGet = cpr::Get(cpr::Url("http://localhost:3000"),
        cpr::Authentication("user", "pass", cpr::AuthMode::BASIC));

    return responseToGet.text;
}

std::string ServerRoutes::FetchDebugPage() {
    cpr::Response responseToGet = cpr::Get(cpr::Url("http://localhost:3000/debug"),
        cpr::Authentication("user", "pass", cpr::AuthMode::BASIC));

    return responseToGet.text;
}

crow::response ServerRoutes::FetchCSSFile() {
    std::string path = "/home/admin/FileShareFrontEnd/src/public/html-objects.css";
    
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    crow::response resp;
    resp.code = 200; 
    resp.add_header("Content-Type", "text/css");
    resp.body = buffer.str();
    AddCORSHeaders(resp);
    return resp;
}

crow::response ServerRoutes::FetchScriptFile() {

    std::string path = "/home/admin/FileShareFrontEnd/src/script.js";

    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    crow::response resp;
    resp.add_header("Content-Type", "application/javascript");
    resp.code = 200;

    resp.body = buffer.str();
    AddCORSHeaders(resp);
    return resp;
}

crow::response ServerRoutes::ValidateLoginAndRedirect(const crow::request& request, Json::Value users, std::string salt) {
    std::string body = request.body;

    crow::query_string parameters(body);

    std::string userNameKey = "username";

    std::string passwordKey = "password";

    std::string userName = parameters.get(userNameKey);

    std::string password = parameters.get(passwordKey);


    crow::response response;
    response.code = 303;

    if (users[userName] == TurnStringSecure::HashString(password, salt)) {

        response.add_header("Location", "/login/successfull");

    }
    else {
        response.add_header("Location", "/login/failed");
    }

    AddCORSHeaders(response);

    return response;

}


void ServerRoutes::AddCORSHeaders(crow::response& response) {

    response.add_header("Access-Control-Allow-Origin", "*");
}
    
