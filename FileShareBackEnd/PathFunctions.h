#include <string>


#ifndef PATH_FUNCTIONS_H
#define PATH_FUNCTIONS_H


class PathFunctions {

public:



	static std::string GetCurrentPath();

	static bool FileExists(std::string &fileName);

	static void CreateFile(std::string& fileName);

	static void DeleteFile(std::string& fileName);


private:

	static void CreateDirectories(std::string& directory);

	static std::string GetFolders(std::string& fullPath);
};



#endif //PathFunctions
