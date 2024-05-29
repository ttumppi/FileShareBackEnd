#include <cstdio>
#include <crow_all.h>
#include <cpr/cpr.h>
#include <Server.h>
#include <json.h>
#include <PathFunctions.h>
#include <ReadWriteJson.h>

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


    _users["Admin"] = "TestPassword";


    std::string currentPath = PathFunctions::GetCurrentPath();

    std::string usersFile = currentPath + "/UserConfigs/Users.json";

    if (PathFunctions::FileExists(usersFile)) {

        Json::Value users = ReadWriteJson::Read(usersFile);

        std::cout << users << std::endl;
    }
    else {

        PathFunctions::CreateFile(usersFile);

        ReadWriteJson::Write(usersFile, _users);
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
    InitializeLoginFiles();
    ReadSaltFromFile();
}
