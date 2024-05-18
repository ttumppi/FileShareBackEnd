#include <cstdio>
#include <crow_all.h>
#include <cpr/cpr.h>


std::string FetchHomePage() {
    cpr::Response responseToGet = cpr::Get(cpr::Url("http://localhost:3000"),
        cpr::Authentication("user", "pass", cpr::AuthMode::BASIC));

    return responseToGet.text;
}
std::string FetchAdvancedPage() {
    cpr::Response responseToGet = cpr::Get(cpr::Url("http://localhost:3000/about"),
        cpr::Authentication("user", "pass", cpr::AuthMode::BASIC));

    return responseToGet.text;
}

int main()
{
    


    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([]() {
        return FetchHomePage();
        });
    CROW_ROUTE(app, "/about")([]() {
        return FetchAdvancedPage();
        });
    app.port(65000).multithreaded().run();
    
    
    
}

