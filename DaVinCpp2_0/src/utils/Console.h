#pragma once
#include <string>
#include <sstream>
#include <iostream>

namespace davincpp 
{

	class Console
	{
	public:
		static void onLoad();
		static void onUpdate();

		static bool clsResized();
		static void resetResizeFlag();

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

		template<class... Args> static const std::string fmtTxt(Args... args)
		{
			std::stringstream output;
			
			(output << ... << args);

			return output.str();
		}

		template<class... Args> static std::string fmtRaw(const char* color, Args... args)
		{
			std::stringstream output;

			output << color;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static std::string fmtLog(Args... args)
		{
			std::stringstream output;

			output << CYAN;
			output << LOG_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static std::string fmtErr(Args... args)
		{
			std::stringstream output;

			output << RED;
			output << ERR_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static std::string fmtOpenglErr(Args... args)
		{
			std::stringstream output;

			output << MAGENTA;
			output << OPENGL_ERR_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		template<class... Args> static std::string fmtWrn(Args... args)
		{
			std::stringstream output;

			output << YELLOW;
			output << WRN_PREFIX;
			(output << ... << args);
			output << "\033[0m";
			output << "\n";

			return output.str().c_str();
		}

		static void printNChar(char c, int count, const char* color);
		static void printCenteredText(std::string_view text, const char* color, char firstChar = ' ', char lastChar = ' ');

		static void clear();
		static void newline();

		static void showCursor(bool show);
		static void setCursor(int row, int xIdx);
		static int getConsoleWidth();
		static int getConsoleHeight();
		static std::pair<int, int> getConsoleSize();
		static char getInputKey();

	private:
#ifndef _WIN32
		static void handle_resize(int sig);
#endif

	public:
		static constexpr const char* LOG_PREFIX			= "[Log]     | ";
		static constexpr const char* ERR_PREFIX			= "[Error]   | ";
		static constexpr const char* OPENGL_ERR_PREFIX	= "[OpenGL]  | ";
		static constexpr const char* WRN_PREFIX			= "[Warning] | ";

		static constexpr const char* RED				= "\x1B[91m";
		static constexpr const char* GRAY				= "\x1B[90m";
		static constexpr const char* CYAN				= "\x1B[36m";
		static constexpr const char* MAGENTA			= "\x1B[95m";
		static constexpr const char* YELLOW				= "\x1B[93m";
		static constexpr const char* GREEN				= "\033[32m";
		static constexpr const char* GREEN_BG_BLACK_FG	= "\033[42;5;30m";

		static constexpr const char KEY_NULL			= '\0';
		static constexpr const char KEY_ARROW_UP		= 72;
		static constexpr const char KEY_ARROW_LEFT		= 75;
		static constexpr const char KEY_ARROW_RIGHT		= 77;
		static constexpr const char KEY_ARROW_DOWN		= 80;
		static constexpr const char KEY_ENTER			= 13;
		static constexpr const char KEY_ESCAPE			= 27;

	private:
#ifdef _WIN32
		static int m_ResizeFlag;
		static int m_ClsWidth, m_ClsHeight;
#else
		static volatile sig_atomic_t m_ResizeFlag;
#endif
	};
}
