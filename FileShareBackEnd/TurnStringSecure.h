#include <string>


#ifndef TURN_STRING_SECURE_H
#define TURN_STRING_SECURE_H

class TurnStringSecure {

public:

	static std::string HashString(std::string& toEncrypt, std::string& salt);

	
};





#endif //TURN_STRING_SECURE_H
