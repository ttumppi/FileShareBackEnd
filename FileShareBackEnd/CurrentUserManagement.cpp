#include <string>
#include <CurrentUserManagement.h>
#include <chrono>
#include <map>
#include <thread>

CurrentUserManagement::CurrentUserManagement() {
	_runState = true;
	std::thread(&CurrentUserManagement::CheckTokens, this).detach();
}

void CurrentUserManagement::AddToken(std::string& token, std::string& user) {

	std::chrono::_V2::system_clock::time_point currentTime = std::chrono::system_clock::now();

	std::chrono::_V2::system_clock::time_point expireDate = currentTime + std::chrono::hours(1);

	_tokens[token] = expireDate;

	_tokensWithUsers[token] = user;
}

bool CurrentUserManagement::ValidToken(std::string& token) {

	return _tokens.find(token) != _tokens.end();
}

void CurrentUserManagement::Close() {
	_runState = false;
}

void CurrentUserManagement::CheckTokens() {

	while (_runState) {

		std::chrono::_V2::system_clock::time_point currentTime = std::chrono::system_clock::now();

		std::map<std::string, std::chrono::_V2::system_clock::time_point>::iterator tokenIterator = _tokens.begin();

		while (tokenIterator != _tokens.end()) {

			if (currentTime > tokenIterator->second) {
				tokenIterator = _tokens.erase(tokenIterator);
				_tokensWithUsers.erase(tokenIterator->first);
			}
			else {
				++tokenIterator;
			}
		}

	}
}

std::string CurrentUserManagement::GetUser(std::string& token) {

	if (_tokensWithUsers.find(token) != _tokensWithUsers.end()) {
		return _tokensWithUsers[token];
	}

	return "";
}