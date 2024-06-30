#include <string>
#include<ManageFiles.h>
#include<PathFunctions.h>
#include<sys/types.h>
#include<dirent.h>
#include<fstream>
#include<json.h>

const std::string& ManageFiles::_savePath = "/media/admin/ExternalStorage/uploadedFiles";

ManageFiles::ManageFiles() {
	ManageFiles::_availableID = CalculateAvailableIdAndInitFileMap();
}

int ManageFiles::CalculateAvailableIdAndInitFileMap() {
	DIR* dirPointer;
	int counter = 0;
	struct dirent* dirEntryPointer;

	dirPointer = opendir(ManageFiles::_savePath.c_str());

	if (dirPointer == NULL) {
		PathFunctions::CreateDirectory(ManageFiles::_savePath);
		dirPointer = opendir(ManageFiles::_savePath.c_str());
	}

	while (dirEntryPointer = readdir(dirPointer)) {
		
		if (dirEntryPointer->d_type == DT_REG) {
			ManageFiles::_fileIDs.insert(std::make_pair(counter, std::string(dirEntryPointer->d_name)));
			counter++;
		}
	}
	closedir(dirPointer);

	return counter + 1;
}

bool ManageFiles::ErrorIfCheckFileNameExists(const std::string& fileName, std::string& errors) {

	if (PathFunctions::FileExists(_savePath + "/" + fileName)) {
		errors = "File exists";
		return true;
	}
	return false;
}

bool ManageFiles::CreatefileFromString(const std::string& data, const int size, const std::string& fileName, std::string& errors) {

	if (ErrorIfCheckFileNameExists(fileName, errors)) {
		return false;
	}

	std::ofstream file(_savePath + "/" + fileName, std::ios::binary);
	file.write(data.c_str(), size);

	_fileIDs.insert({ ManageFiles::_availableID, fileName });
	_availableID++;

	return true;

}

Json::Value ManageFiles::GetAllFiles() {

	Json::Value values;

	for (std::pair<int, std::string> pair : _fileIDs) {
		values[std::to_string(pair.first)] = pair.second;
	}

	return values;
}

std::string ManageFiles::GetFileData(const int id, std::string& errors, std::string& fileName) {
	fileName = _fileIDs.find(id)->second;


	if (!PathFunctions::FileExists(_savePath + "/" + fileName)) {
		errors = "File not found";
		return "";
	}

	std::ifstream file(_savePath + "/" + fileName, std::ios::binary | std::ios::ate);

	std::ifstream::pos_type fileSize = file.tellg();

	file.seekg(0, std::ios::beg);

	char* buffer = new char[fileSize];

	file.read(buffer, fileSize);
	file.close();

	std::string data(buffer, fileSize);

	delete[] buffer;

	return data;
}