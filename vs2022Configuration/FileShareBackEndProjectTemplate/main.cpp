#include <cstdio>
#include <crow_all.h>
#include <cpr/cpr.h>
#include <Server.h>
#include <json.h>
#include <PathFunctions.h>
#include <ReadWriteJson.h>
#include <TurnStringSecure.h>

void InitializeLoginFiles();
void ReadSaltFromFile();
void ProcedureBeforeServerStart();


Json::Value _users;
std::string _salt;

int main()
{
    ProcedureBeforeServerStart();


    Server server;
    server.Start();
    
}

void InitializeLoginFiles() {

    std::cout << "Starting" << std::endl;


    std::string currentPath = PathFunctions::GetCurrentPath();

    std::string usersFile = currentPath + "/UserConfigs/Users.json";

    if (PathFunctions::FileExists(usersFile)) {

        Json::Value _users = ReadWriteJson::Read(usersFile);
    }
    else {

        std::cout << "No user logins found, shutting down!" << std::endl;
        exit(EXIT_FAILURE);
    }

}

void ReadSaltFromFile() {
    std::ifstream salt;
    std::string filePath = PathFunctions::GetCurrentPath() +
        "/UserConfigs/Secure.txt";

    if (PathFunctions::FileExists(filePath)) {
        salt.open(filePath);
        std::getline(salt, _salt);
        salt.close();
        PathFunctions::DeleteFile(filePath);
    }
    else {
        std::cout << "Closing software, security file not found!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ProcedureBeforeServerStart() {
    ReadSaltFromFile();
    InitializeLoginFiles();
    
}
