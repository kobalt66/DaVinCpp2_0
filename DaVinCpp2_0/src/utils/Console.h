#pragma once

#include <xstring>
#include <iostream>

namespace davincpp 
{
	class Console
	{
	public:
		template<class... Args> static void raw(const char* color, Args... args)
		{
			std::cout << color;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void log(Args... args)
		{
			std::cout << CYAN;
			std::cout << LOG_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void err(Args... args)
		{
			std::cout << RED;
			std::cout << ERR_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void openglErr(Args... args)
		{
			std::cout << MAGENTA;
			std::cout << OPENGL_ERR_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static void wrn(Args... args)
		{
			std::cout << YELLOW;
			std::cout << WRN_PREFIX;
			(std::cout << ... << args);
			std::cout << "\033[0m";
			newline();
		}

		template<class... Args> static const char* fmtRaw(Args... args, const char* color = GRAY)
		{
			std::stringstream output;

			output << color;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static const char* fmtLog(Args... args)
		{
			std::stringstream output;

			output << CYAN;
			output << LOG_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static const char* fmtErr(Args... args)
		{
			std::stringstream output;

			output << RED;
			output << ERR_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static const char* fmtOpenglErr(Args... args)
		{
			std::stringstream output;

			output << MAGENTA;
			output << OPENGL_ERR_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static const char* fmtWrn(Args... args)
		{
			std::stringstream output;

			output << YELLOW;
			output << WRN_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
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

		static constexpr const char* RED		= "\x1B[91m";
		static constexpr const char* GRAY		= "\x1B[90m";
		static constexpr const char* CYAN		= "\x1B[36m";
		static constexpr const char* MAGENTA	= "\x1B[95m";
		static constexpr const char* YELLOW		= "\x1B[93m";
	};
}
