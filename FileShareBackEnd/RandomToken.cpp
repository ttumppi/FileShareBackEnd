#include <string>
#include <random>
#include <RandomToken.h>

char RandomToken::_alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 
'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z'};


RandomToken::RandomToken() {
	unsigned int timeOfStart = static_cast<unsigned int>(time(NULL));
	srand(timeOfStart);
}

std::string RandomToken::GetRandomToken(const int& length) {

	char* token = new char[length + 1];

	for (int i = 0; i < length; i++) {

		int value = rand() % sizeof(_alphabet) / sizeof(_alphabet[0]);
		token[i] = _alphabet[value];
	}

	token[length] = '\0';

	return std::string(token);
}