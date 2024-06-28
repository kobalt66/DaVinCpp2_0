#include "DaVinCppFileSystem.h"
#include <Console.h>
#include <fstream>
#include <DaVinCppExceptions.h>

namespace davincpp
{
	std::string DaVinCppFileSystem::readFile(std::string_view path)
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

		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		return buffer.str();
	}
	
	bool DaVinCppFileSystem::exists(std::string_view path)
	{
		return std::filesystem::exists(path);
	}
}