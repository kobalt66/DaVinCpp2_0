#pragma once

#include <xstring>
#include <iostream>
#include <color-console/color.hpp>

namespace davincpp 
{
	class Console
	{
	public:
		template<class... Args> static void raw(Args... args)
		{
			(std::cout << ... << dye::grey(args));
			newline();
		}

		template<class... Args> static void log(Args... args)
		{
			std::cout << dye::aqua(LOG_PREFIX);
			(std::cout << ... << dye::aqua(args));
			newline();
		}

		template<class... Args> static void err(Args... args)
		{
			std::cout << dye::red(ERR_PREFIX);
			(std::cout << ... << dye::red(args));
			newline();
		}

		template<class... Args> static void wrn(Args... args)
		{
			std::cout << dye::yellow(WRN_PREFIX);
			(std::cout << ... << dye::yellow(args));
			newline();
		}

		static void clear() {
#ifdef _WIN32
			std::system("cls");
#else
			std::system("clear");
#endif
		}

		static void newline()
		{
			std::cout << "\n";
		}

	public:
		static constexpr const char* LOG_PREFIX = "[Log]     | ";
		static constexpr const char* ERR_PREFIX = "[Error]   | ";
		static constexpr const char* WRN_PREFIX = "[Warning] | ";
	};
}
