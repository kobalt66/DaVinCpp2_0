#pragma once
#include <string>
#include <vector>

namespace davincpp
{
	class DaVinCppString
	{
	public:
		static std::vector<std::string> split(std::string_view input, char delimiter);
	};
}
