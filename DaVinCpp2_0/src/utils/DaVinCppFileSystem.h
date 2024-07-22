#pragma once
#include <filesystem>

namespace davincpp
{
	class DaVinCppFileSystem
	{
	public:
		static std::string readFile(std::string_view inputPath);
		static bool exists(std::string_view inputPath);
		static std::string prepareFilePath(const char* path);
	};
}
