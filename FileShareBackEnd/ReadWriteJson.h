#include <string>
#include <json.h>

#ifndef READ_WRITE_JSON
#define READ_WRITE_JSON

class ReadWriteJson{

public:

	static void Write(std::string path, Json::Value json);

	static Json::Value Read(std::string& path);
};


#endif // !READ_WRITE_JSON

