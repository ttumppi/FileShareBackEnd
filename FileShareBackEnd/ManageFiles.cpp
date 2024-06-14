#include <string>
#include<ManageFiles.h>
#include<PathFunctions.h>
#include<sys/types.h>
#include<dirent.h>
#include<fstream>

const std::string& ManageFiles::_savePath = PathFunctions::GetCurrentPath() + "/uploadedFiles";

ManageFiles::ManageFiles() {
	ManageFiles::_availableID = CalculateAvailableIdAndInitFileMap();
}

int ManageFiles::CalculateAvailableIdAndInitFileMap() {
	DIR* dirPointer;
	int counter = 0;
	struct dirent* dirEntryPointer;

	dirPointer = opendir(ManageFiles::_savePath.c_str());

	if (dirPointer == NULL) {
		std::string nonConstant;
		nonConstant.assign(ManageFiles::_savePath);
		PathFunctions::CreateFile(nonConstant);
		dirPointer = opendir(ManageFiles::_savePath.c_str());
	}

	while (dirEntryPointer = readdir(dirPointer)) {
		counter++;
		if (dirEntryPointer->d_type == DT_REG) {
			ManageFiles::_fileIDs.insert(std::make_pair(counter, std::string(dirEntryPointer->d_name)));
		}
		closedir(dirPointer);
	}

	return counter + 1;
}

bool ManageFiles::ErrorIfCheckFileNameExists(const std::string& fileName, std::string& errors) {

	if (PathFunctions::FileExists(fileName)) {
		errors = "File exists";
		return false;
	}
	return true;
}

bool ManageFiles::CreatefileFromString(const std::string& data, const int size, const std::string& fileName, std::string& errors) {

	if (ErrorIfCheckFileNameExists(fileName, errors)) {
		return false;
	}

	std::ofstream file(fileName, std::ios::binary);
	file.write(data.c_str(), size);
	return true;

}