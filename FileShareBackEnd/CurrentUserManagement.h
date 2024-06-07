#ifndef CURRENT_USER_MANAGEMENT_H
#define CURRENT_USER_MANAGEMENT_H
#include <string>
#include <map>
#include <chrono>

class CurrentUserManagement {
public:

	CurrentUserManagement();

	bool ValidToken(std::string& token);

	void AddToken(std::string& token, std::string& user);

	void Close();

	std::string GetUser(std::string& token);

private:

	void CheckTokens();


	
	std::map<std::string, std::chrono::_V2::system_clock::time_point> _tokens;
	std::map<std::string, std::string> _tokensWithUsers;
	bool _runState;

};


#endif //CURRENT_USER_MANAGEMENT_H 
