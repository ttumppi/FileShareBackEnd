#include <string>
#include <openssl/pem.h>
#include <TurnStringSecure.h>

std::string TurnStringSecure::HashString(std::string& toEncrypt, std::string& salt) {
	std::string withSalt = toEncrypt + salt;

	EVP_MD_CTX* context = EVP_MD_CTX_new();

	EVP_DigestInit_ex(context, EVP_sha1(), nullptr);

	EVP_DigestUpdate(context, withSalt.c_str(), withSalt.size());

	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int lengthOfHash = 0;

	EVP_DigestFinal_ex(context, hash, &lengthOfHash);

	EVP_MD_CTX_free(context);

	std::string hashInString = "";
	
	for (int i = 0; i < lengthOfHash; i++) {
		int hashNumber = static_cast<int>(hash[i]);
		hashInString += std::to_string(hashNumber);
	}


	return hashInString;
}

