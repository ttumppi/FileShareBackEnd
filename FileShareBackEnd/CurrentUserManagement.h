#ifndef CURRENT_USER_MANAGEMENT_H
#define CURRENT_USER_MANAGEMENT_H
#include <string>
#include <map>
#include <chrono>

class CurrentUserManagement {
public:

	CurrentUserManagement();

	bool ValidToken(std::string& token);

	void AddToken(std::string& token);

	void Close();

private:

	void CheckTokens();


	
	std::map<std::string, std::chrono::_V2::system_clock::time_point> _tokens;
	bool _runState;

};


#endif //CURRENT_USER_MANAGEMENT_H 
