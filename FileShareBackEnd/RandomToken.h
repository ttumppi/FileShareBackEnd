#ifndef RANDOM_TOKEN_H
#define RANDOM_TOKEN_H
#include <string>
#include <random>

class RandomToken {
public:

	RandomToken();

	std::string GetRandomToken(const int& length);


private:
	static char _alphabet[];

};


#endif //RANDOM_TOKEN_H