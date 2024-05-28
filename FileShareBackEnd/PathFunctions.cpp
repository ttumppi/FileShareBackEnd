#define _CRT_SECURE_NO_DEPRECATE
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <PathFunctions.h>

PathFunctions::PathFunctions() {

}



std::string PathFunctions::GetCurrentPath() {

	return std::filesystem::current_path().string();
}


bool PathFunctions::FileExists(std::string &fileName) {

	if (FILE* file = fopen(fileName.c_str(), "r")) {
		fclose(file);
		return true;
	}
	return false;
}

void PathFunctions::CreateFile(std::string& fileName) {

	CreateDirectories(fileName);

	std::ofstream file(fileName);
	file.close();
}

void PathFunctions::CreateDirectories(std::string& directories) {

	if (FileExists(directories)) {
		return;
	}
	std::filesystem::create_directories(directories);
}