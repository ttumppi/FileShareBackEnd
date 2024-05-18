#include <cstdio>
#include <crow_all.h>
#include <cpr/cpr.h>


int main()
{
    cpr::Response responseToGet = cpr::Get(cpr::Url("http://localhost:3000/test"),
        cpr::Authentication("user", "pass", cpr::AuthMode::BASIC));

    std::cout << responseToGet.status_code;

    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });
    app.port(65000).multithreaded().run();
    
    
    
}