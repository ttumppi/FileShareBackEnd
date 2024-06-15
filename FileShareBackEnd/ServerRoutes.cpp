#include <cstdio>
#include <string>
#include <crow_all.h>
#include <cpr/cpr.h>
#include <ServerRoutes.h>
#include <json.h>
#include <TurnStringSecure.h>
#include <RandomToken.h>
#include <ManageFiles.h>
#include <StringParser.h>

ServerRoutes::ServerRoutes(CurrentUserManagement& sessionManagement) : _sessionManagement(sessionManagement) {
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
    std::string body = '?' + request.body;

    crow::query_string parameters(body.c_str());

    std::string userNameKey = "username";

    std::string passwordKey = "password";

    char* userNamePointer = parameters.get(userNameKey);


    char* passwordPointer = parameters.get(passwordKey);

    if (userNamePointer == nullptr || passwordPointer == nullptr) {
        crow::response errorResponse;
        errorResponse.code = 303;
        errorResponse.add_header("Location", "/login/failed");
        AddCORSHeaders(errorResponse);
        return errorResponse;
    }


    std::string password = std::string(passwordPointer);

    std::string userName = std::string(userNamePointer);

    crow::response response;
    response.code = 303;

    std::string enteredPassword = TurnStringSecure::HashString(password, salt);

    std::string test = users[userName].asString();

    if (users[userName].asString() == enteredPassword) {

        response.add_header("Location", "/login/successfull");

        std::string token = _tokenGenerator.GetRandomToken(20);

        _sessionManagement.AddToken(token, userName);
        response.set_header("Set-Cookie", token);
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
    
crow::response ServerRoutes::SaveFile(const crow::request& request) {

    crow::multipart::message message = crow::multipart::message(request);
    std::string fileName;
    std::string data;

    for (crow::multipart::part messagePart : message.parts) {

        
        crow::multipart::mph_map::iterator contentHeader = messagePart.headers.find("Content-Disposition");

        if (contentHeader == messagePart.headers.end()) {
            continue;
        }

        std::string contentHeaderValue = contentHeader->second.value;

        

        std::string tryGetFileName = StringParser::FindValueWithKey("filename", contentHeaderValue, ';');

        if (tryGetFileName.empty()) {
            continue;
        }
        
        data = messagePart.body;
    }

    

    crow::response redirect;
    redirect.code = 303;

    if (fileName == "" || data == "") {
        redirect.add_header("Location", "/upload");
        AddCORSHeaders(redirect);
        return redirect;
    }

    std::string errors = "";
    if (!_manageFiles.CreatefileFromString(data, data.size(), fileName, errors)) {
        redirect.add_header("Location", "/upload/failed");
        redirect.add_header("Errors", errors);
        AddCORSHeaders(redirect);
        return redirect;
    }

    redirect.add_header("Location", "/upload/success");
    AddCORSHeaders(redirect);
    return redirect;
}

crow::response ServerRoutes::GetAllFiles() {
    Json::Value files = _manageFiles.GetAllFiles();

    crow::response response;
    response.code = 200;
    response.set_header("Content-Type", "application/json");
    response.body = files.asString();

    return response;
}

crow::response ServerRoutes::GetFileData(const int id) {

    std::string errors;
    std::string fileName;
    std::string data = _manageFiles.GetFileData(id, errors, fileName);

    crow::response response;

    if (!errors.empty()) {
        response.code = 303;
        response.add_header("Location", "/download/failed");
        response.add_header("Errors", errors);
        AddCORSHeaders(response);
        return response;
    }

    std::ostringstream contentHeaderValue;
    contentHeaderValue << "attachment; filename=\"" << fileName << "\"";

    response.code = 200;
    response.add_header("Content-Type", "application/octet-stream");
    response.add_header("Content-Disposition", contentHeaderValue.str());

    response.body = data;

    return response;

}
