#include <cstdio>
#include <crow_all.h>



int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });
    app.port(65000).multithreaded().run();
}