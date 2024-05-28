#include <string>


#ifndef PATH_FUNCTIONS_H
#define PATH_FUNCTIONS_H


class PathFunctions {

public:


	PathFunctions();

	std::string GetCurrentPath();

	bool FileExists(std::string &fileName);

	void CreateFile(std::string& fileName);

	


private:

	void CreateDirectories(std::string& directory);
};



#endif //PathFunctions
