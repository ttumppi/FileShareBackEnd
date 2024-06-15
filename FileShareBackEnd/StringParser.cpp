#include<string>
#include<StringParser.h>

std::string StringParser::FindValueWithKey(const std::string& key, const std::string& toParse, const char endTag) {

	size_t resultPos = toParse.find(key);
	if (resultPos == std::string::npos) {
		return "";
	}

	size_t endPosOfKey = resultPos + key.size();

	if (toParse.size() == endPosOfKey) {
		return "";
	}

	std::string result;

	for (int i = endPosOfKey; i < toParse.size(); i++) {
		if (toParse[i] == '=' || toParse[i] == '\"') {
			continue;
		}

		if (toParse[i] == endTag) {
			break;
		}
		else{
			result += toParse[i];
		}

	}

	return result;
}
