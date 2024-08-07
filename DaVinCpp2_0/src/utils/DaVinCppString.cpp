#include "DaVinCppString.h"
#include <sstream>
#include <string>

namespace davincpp
{
	std::vector<std::string> DaVinCppString::split(std::string_view input, char delimiter)
	{
		std::vector<std::string> tokens;
		std::istringstream ss(input.data());

		std::string token;
		while (std::getline(ss, token, delimiter)) {
			tokens.push_back(token);
		}

		return tokens;
	}

	std::string DaVinCppString::findReplace(std::string_view input, std::string_view find, std::string_view replace)
	{
		std::string str = input.data();

		size_t pos = str.find(find.data());
		if (pos != std::string::npos) {
			str.replace(pos, find.length(), replace);

			if (str.at(pos) == '\0') {
				str.erase(pos);
			}
		}

		return str;
	}

	std::string DaVinCppString::findReplaceAll(std::string_view input, std::string_view find, std::string_view replace)
	{
		std::string str = input.data();

		size_t pos = str.find(find.data());
		while (pos != std::string::npos) {
			str.replace(pos, find.length(), replace);

			if (str.at(pos) == '\0') {
				str.erase(pos);
			}
		}

		return str;
	}
}
