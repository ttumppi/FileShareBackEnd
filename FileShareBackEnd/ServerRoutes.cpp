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
#include <ReadWriteJson.h>

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

        response.add_header("Location", "/homepage");

        std::string token = _tokenGenerator.GetRandomToken(20);

        _sessionManagement.AddToken(token, userName);

        std::string tokenCookie = "accessToken=" + token + ";";
        response.set_header("Set-Cookie", tokenCookie);
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
        std::unordered_map<std::string, std::string> contentHeaderValues = contentHeader->second.params;

        

        for (std::pair<std::string, std::string> param : contentHeaderValues) {
            if (param.first == "filename") {
                fileName = param.second;
                break;
            }
        }
        

        if (fileName.empty()) {
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

crow::response ServerRoutes::GetAllFiles(const crow::request& request) {
    Json::Value files = _manageFiles.GetAllFiles();

    std::string sessionToken = request.get_header_value("Cookie");
    std::string token = StringParser::FindValueWithKey("accessToken", sessionToken, ';');

    int userLevel = GetUserLevel(token);

    Json::Value responseJson;

    responseJson["UserLevel"] = userLevel;

    responseJson["files"] = files;

    std::string filesInString = ReadWriteJson::JsonToString(responseJson);

    if (filesInString.empty() || filesInString == "null") {
        filesInString = "{}";
    }
    cpr::Body body = cpr::Body(filesInString);
    cpr::Response response = cpr::Post(cpr::Url("http://localhost:3000/files"), body, 
        cpr::Header{{"Content-Type", "application/json"}});

    crow::response resp;

    resp.code = 200;

    resp.body = response.text;

    AddCORSHeaders(resp);
    return resp;
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

    AddCORSHeaders(response);

    response.body = data;

    return response;

}

crow::response ServerRoutes::FetchButtonScript() {

    std::string path = "/home/admin/FileShareFrontEnd/src/button-functions.js";

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

crow::response ServerRoutes::DeleteFile(const int& id) {
    
    crow::response resp;

    if (_manageFiles.RemoveFile(id)) {
        resp.code = 200;
    }

    resp.code = 300;
    
    AddCORSHeaders(resp);
    return resp;
}

int ServerRoutes::GetUserLevel(std::string& token) {

    std::string user = _sessionManagement.GetUser(token);


    if (user == "") {
        return 0;
    }

    if (user == "SlaveToTheCode") {
        return 1;
    }
    else {
        return 0;
    }
}
