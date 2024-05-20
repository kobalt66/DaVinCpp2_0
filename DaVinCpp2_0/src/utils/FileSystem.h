#pragma once
#include <filesystem>

namespace davincpp
{
	class FileSystem
	{
	public:
		static std::string_view readFile(std::string_view path);
		static bool exists(std::string_view path);
	};
}
