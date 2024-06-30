#include <string>


#ifndef PATH_FUNCTIONS_H
#define PATH_FUNCTIONS_H


class PathFunctions {

public:



	static std::string GetCurrentPath();

	static bool FileExists(const std::string &fileName);

	static void CreateFile(const std::string& fileName);

	static void DeleteFile(const std::string& fileName);

	static void CreateDirectory(const std::string& dir);


private:

	static void CreateDirectories(const std::string& directory);

	static std::string GetFolders(const std::string& fullPath);
};



#endif //PathFunctions
