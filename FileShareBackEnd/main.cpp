#include <cstdio>
#include <crow_all.h>
#include <cpr/cpr.h>
#include <Server.h>
#include <json.h>
#include <PathFunctions.h>
#include <ReadWriteJson.h>

void InitializeLoginFiles();


int main()
{
    InitializeLoginFiles();

    Server server;
    server.Start();
    
}

void InitializeLoginFiles() {

    std::cout << "Starting" << std::endl;

    Json::Value users;

    users["Admin"] = "TestPassword";

    PathFunctions pathTools;

    ReadWriteJson jsonTools;

    std::string currentPath = pathTools.GetCurrentPath();

    std::string usersFile = currentPath + "/UserConfigs/Users.json";

    if (pathTools.FileExists(usersFile)) {

        Json::Value users = jsonTools.Read(usersFile);

        std::cout << users;
    }
    else {

        pathTools.CreateFile(usersFile);

        jsonTools.Write(usersFile, users);
    }

}
