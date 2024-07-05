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
}
