#define _CRT_SECURE_NO_DEPRECATE
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <PathFunctions.h>




std::string PathFunctions::GetCurrentPath() {

	return std::filesystem::current_path().string();
}


bool PathFunctions::FileExists(const std::string &fileName) {

	if (FILE* file = fopen(fileName.c_str(), "r")) {
		fclose(file);
		return true;
	}
	return false;
}

void PathFunctions::CreateFile(const std::string& fileName) {

	CreateDirectories(fileName);

	std::ofstream file(fileName);
	file.close();
}

void PathFunctions::CreateDirectories(const std::string& directories) {

	std::string folders = GetFolders(directories);

	if (FileExists(folders)) {
		return;
	}
	std::filesystem::create_directories(folders);
}

std::string PathFunctions::GetFolders(const std::string& fullPath) {

	int lastIndex;

	for (int i = fullPath.length() - 1; i--;) {
		if (fullPath[i] == '/' || fullPath[i] == '\\') {
			lastIndex = i;
			break;
		}
	}

	while (fullPath[lastIndex] == '\\') {
		lastIndex--;
	}



	return  fullPath.substr(0, lastIndex);
}

void PathFunctions::DeleteFile(const std::string& fileName) {

	if (FileExists(fileName)) {
		std::filesystem::remove(fileName);
	}
}