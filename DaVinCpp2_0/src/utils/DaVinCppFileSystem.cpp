#include "DaVinCppFileSystem.h"
#include <Console.h>
#include <fstream>
#include <DaVinCppExceptions.h>
#include <DaVinCppString.h>
#include <DaVinCppConstants.h>

namespace davincpp
{
	std::string DaVinCppFileSystem::readFile(std::string_view inputPath)
	{
		std::string path = DaVinCppFileSystem::prepareFilePath(inputPath.data());

		if (!exists(path)) {
			Console::err("The file at '", path, "' doesn't exist!");
			throw system_error();
		}

		std::fstream fileStream(path.data());
		if (!fileStream.good()) {
			Console::err("Something went wrong while trying to access the target file at '", path, "'!");
			throw system_error();
		}

		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		return buffer.str();
	}

	bool DaVinCppFileSystem::exists(std::string_view inputPath)
	{
		return std::filesystem::exists(DaVinCppFileSystem::prepareFilePath(inputPath.data()));
	}

	std::string DaVinCppFileSystem::prepareFilePath(const char* path)
	{
		std::string output = path;
		output = DaVinCppString::findReplace(output, "[BASE_DIR]", BASE_DIR);
		output = DaVinCppString::findReplace(output, "[TEST_ENV]", TEST_ENV);
#ifdef _WIN32
		output = DaVinCppString::findReplaceAll(output, "/", "\\");
#endif
		return output;
	}

	std::pair<std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>> DaVinCppFileSystem::getContentsOfDirectory(const std::filesystem::path& directoryPath)
	{
		std::vector<std::filesystem::directory_entry> directories, files;

		for (const auto& item : std::filesystem::directory_iterator(directoryPath)) {
			if (item.is_directory()) {
				directories.emplace_back(item);
			}
			else {
				files.emplace_back(item);
			}
		}

		return { directories, files };
	}

}