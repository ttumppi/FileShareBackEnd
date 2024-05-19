#include <cstdio>
#include <string>
#include <crow_all.h>
#include <cpr/cpr.h>
#include <ServerRoutes.h>

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
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        return crow::response(404, "File not found");
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        return crow::response(500, "Error reading file");
    }

    crow::response resp;
    resp.code = 200; // HTTP OK
    resp.add_header("Content-Type", "text/css");
    resp.body = std::string(buffer.begin(), buffer.end());
    return resp;
}


    
