#include <string>
#include <json.h>
#ifndef READ_WRITE_JSON
#define READ_WRITE_JSON

class ReadWriteJson{

public:

	static void Write(std::string path, Json::Value json);

	static Json::Value Read(std::string& path);

	static std::string JsonToString(const Json::Value& json);

private:
	static Json::StreamWriterBuilder _writer;
};


#endif // !READ_WRITE_JSON

