#pragma once

#include <xstring>
#include <iostream>

namespace davincpp 
{
	class Console
	{
	public:
		template<class... Args> static void raw(Args... args)
		{
			std::cout << "\x1B[90m";
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void log(Args... args)
		{
			std::cout << "\x1B[36m";
			std::cout << LOG_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void err(Args... args)
		{
			std::cout << "\x1B[91m";
			std::cout << ERR_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void openglErr(Args... args)
		{
			std::cout << "\x1B[95m";
			std::cout << OPENGL_ERR_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void wrn(Args... args)
		{
			std::cout << "\x1B[93m";
			std::cout << WRN_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
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
		static constexpr const char* LOG_PREFIX			= "[Log]     | ";
		static constexpr const char* ERR_PREFIX			= "[Error]   | ";
		static constexpr const char* OPENGL_ERR_PREFIX	= "[OpenGL]  | ";
		static constexpr const char* WRN_PREFIX			= "[Warning] | ";
	};
}
