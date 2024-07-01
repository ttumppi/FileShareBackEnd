#ifndef MANAGE_FILES_H
#define MANAGE_FILES_H

#include <string>
#include <PathFunctions.h>
#include <map>
#include <json.h>

class ManageFiles {
public:
	ManageFiles();

	bool CreatefileFromString(const std::string& data, const int size, const std::string& fileName, std::string& errors);
	
	Json::Value GetAllFiles();

	std::string GetFileData(const int id, std::string& errors, std::string& filename);

	bool RemoveFile(const int& fileID);

private:

	int CalculateAvailableIdAndInitFileMap();

	bool ErrorIfCheckFileNameExists(const std::string& fileName, std::string& errors);

	static const std::string& _savePath;

	std::map<int, std::string> _fileIDs;

	int _availableID;
};



#endif // MANAGE_FILES_H
