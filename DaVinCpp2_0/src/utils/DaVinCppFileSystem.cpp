#include "DaVinCppFileSystem.h"
#include <Console.h>
#include <fstream>
#include <DaVinCppExceptions.h>
#include <DaVinCppString.h>
#include <DaVinCppConstants.h>

namespace davincpp
{
	void DaVinCppFileSystem::writeFile(const std::filesystem::path& path, std::string_view data)
	{
		std::filesystem::path finalPath = prepareFilePath(path);

		if (!canReadWrite(finalPath)) {
			throw system_error(Console::fmtTxt("Failed to write data to file at ", finalPath, ": You are not allowed to read or write at this location!"));
		}

		std::ofstream fileStream(finalPath);
		if (!fileStream.is_open()) {
			throw system_error(Console::fmtTxt("Something went wrong while trying to access the target file at ", finalPath, "!"));
		}

		fileStream << data;
		fileStream.close();
	}

	std::string DaVinCppFileSystem::readFile(const std::filesystem::path& path)
	{
		std::filesystem::path finalPath = prepareFilePath(path);

		if (!exists(finalPath)) {
			throw system_error(Console::fmtTxt("The file at ", finalPath, " doesn't exist!"));
		}

		if (!canReadWrite(finalPath)) {
			throw system_error(Console::fmtTxt("Failed to read data from file at ", finalPath, ": You are not allowed to read or write at this location!"));
		}

		std::fstream fileStream(finalPath);
		if (!fileStream.good()) {
			throw system_error(Console::fmtTxt("Something went wrong while trying to access the target file at ", finalPath, "!"));
		}

		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		return buffer.str();
	}


	bool DaVinCppFileSystem::exists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(prepareFilePath(path));
	}

	bool DaVinCppFileSystem::canReadWrite(const std::filesystem::path& path)
	{
		return canRead(path) && canWrite(path);
	}

	bool DaVinCppFileSystem::canRead(const std::filesystem::path& path)
	{
		return status(path).permissions() == std::filesystem::perms::group_read;
	}

	bool DaVinCppFileSystem::canWrite(const std::filesystem::path& path)
	{
		return status(path).permissions() == std::filesystem::perms::group_write;
	}


	std::filesystem::path DaVinCppFileSystem::prepareFilePath(const std::filesystem::path& path)
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
		std::filesystem::path finalPath = prepareFilePath(directoryPath);

		if (!exists(finalPath)) {
			throw system_error(Console::fmtTxt("Failed to read data to directory at ", finalPath, ": The directory path is invalid!"));
		}

		std::vector<std::filesystem::directory_entry> directories, files;

		for (const auto& item : std::filesystem::directory_iterator(finalPath)) {
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