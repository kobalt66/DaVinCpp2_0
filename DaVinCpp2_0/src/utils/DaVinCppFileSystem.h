#pragma once
#include <filesystem>
#include <vector>

namespace davincpp
{
	class DaVinCppFileSystem
	{
	public:
		static void writeFile(const std::filesystem::path& path, std::string_view data);
		static std::string readFile(const std::filesystem::path& path);

		static bool exists(const std::filesystem::path& path);
		static bool canReadWrite(const std::filesystem::path& path);
		static bool canRead(const std::filesystem::path& path);
		static bool canWrite(const std::filesystem::path& path);

		static std::filesystem::path prepareFilePath(const std::filesystem::path& path);

		/// Returns two lists of file paths.
		/// 1. All sub directories inside the target directory
		/// 2. All files inside the target directory
		static std::pair<std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>> getContentsOfDirectory(const std::filesystem::path& directoryPath);
	};
}
