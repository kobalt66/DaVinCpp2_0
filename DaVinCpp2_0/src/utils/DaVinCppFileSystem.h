#pragma once
#include <filesystem>
#include <vector>

namespace davincpp
{
	class DaVinCppFileSystem
	{
	public:
		static std::string readFile(std::string_view inputPath);
		static bool exists(std::string_view inputPath);
		static std::string prepareFilePath(const char* path);

		/// Returns two lists of file paths.
		/// 1. All sub directories inside the target directory
		/// 2. All files inside the target directory
		static std::pair<std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>> getContentsOfDirectory(const std::filesystem::path& directoryPath);
	};
}
