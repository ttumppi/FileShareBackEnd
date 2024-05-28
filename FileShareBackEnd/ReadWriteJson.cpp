#include <string>
#include <json.h>
#include <fstream>
#include <ReadWriteJson.h>

void ReadWriteJson::Write(std::string path, Json::Value json) {

    std::ofstream file(path);

    Json::StyledWriter styledWriter;
    file << styledWriter.write(json);
    file.close();
}

Json::Value ReadWriteJson::Read(std::string& path) {
    std::ifstream file(path);
    Json::Value toRead;
    file >> toRead;

    return toRead;
}