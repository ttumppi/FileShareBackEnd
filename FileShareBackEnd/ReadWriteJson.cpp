#include <string>
#include <json.h>
#include <fstream>
#include <ReadWriteJson.h>

Json::StreamWriterBuilder ReadWriteJson::_writer;

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

std::string ReadWriteJson::JsonToString(const Json::Value& json) {
    
    return Json::writeString(ReadWriteJson::_writer, json);
}