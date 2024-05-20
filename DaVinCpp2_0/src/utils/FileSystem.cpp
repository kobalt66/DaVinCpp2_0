#include "FileSystem.h"
#include <Console.h>
#include <fstream>
#include <DaVinCppExceptions.h>

namespace davincpp
{
	std::string_view FileSystem::readFile(std::string_view path)
	{
		if (!exists(path)) {
			Console::err("The file at '", path, "' doesn't exist!");
			throw system_error();
		}

		std::fstream fileStream(path.data());
		if (!fileStream.good()) {
			Console::err("Something went wrong while trying to access the target file at '", path, "'!");
			throw system_error();
		}
	}
	
	bool FileSystem::exists(std::string_view path)
	{
		return std::filesystem::exists(path);
	}
}