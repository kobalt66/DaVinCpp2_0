#pragma once
#include <string>
#include <sstream>
#include <iostream>
#if !defined(_WIN32) && !defined(DAVSCRIPT_UNIT_TEST)
#include <csignal>
#include <ncurses/curses.h>
#endif

namespace davincpp 
{
	class Console
	{
	public:
		static void onLoad();
		static void onUpdate();

		static void loadNcurses();
		static void shutDownNcurses();
		static void resizeNcurses();

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

		template<class... Args> static std::string fmtTxt(Args... args)
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

#if defined(_WIN32) || defined(DAVSCRIPT_UNIT_TEST)
		static void printNChar(char c, int count, const char* color);
		static void printCenteredText(std::string_view text, const char* color, char firstChar = ' ', char lastChar = ' ');
#else
		static void printCenteredText(std::string_view text, int colorPair, int cliY);
		static void printText(std::string_view text, int colorPair, int cliY);
		static void printNChar(int c, int colorPair, int length, int cliX, int cliY);
		static void printTextMarginL(std::string_view textLeft, int colorPair, int cliY, int marginLeft);
		static void printTextMarginR(std::string_view textRight, int colorPair, int cliY, int marginRight);
		static void printTextMarginLR(std::string_view textLeft, std::string_view textRight, int colorPair, int cliY, int marginLeft, int marginRight);
#endif

		static void clear();
		static void newline();

		static void showCursor(bool show);
		static void setCursor(int row, int xIdx);
		static int getConsoleWidth();
		static int getConsoleHeight();
		static std::pair<int, int> getConsoleSize();

		static int getInputKey();
		static std::string getInputKeyByCode(int keyCode);
		static int awaitKeyInput();

	private:
#if !defined(_WIN32) && !defined(DAVSCRIPT_UNIT_TEST)
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

#if !defined(_WIN32) && !defined(DAVSCRIPT_UNIT_TEST)
		static constexpr int GREEN_BLACK_PAIR	= 1;
		static constexpr int BLACK_GREEN_PAIR	= 2;
		static constexpr int BLACK_YELLOW_PAIR	= 3;
#endif

#if defined(_WIN32) || defined(DAVSCRIPT_UNIT_TEST)
		static constexpr int KEY_NULL			= -1;
		static constexpr int KEY_ARROW_UP		= 72;
		static constexpr int KEY_ARROW_LEFT		= 75;
		static constexpr int KEY_ARROW_RIGHT	= 77;
		static constexpr int KEY_ARROW_DOWN		= 80;
		static constexpr int KEY_NEWLINE		= 13;
		static constexpr int KEY_ESCAPE			= 27;
#else
		static constexpr int KEY_NULL			= ERR;
		static constexpr int KEY_ARROW_UP		= KEY_UP;
		static constexpr int KEY_ARROW_LEFT		= KEY_LEFT;
		static constexpr int KEY_ARROW_RIGHT	= KEY_RIGHT;
		static constexpr int KEY_ARROW_DOWN		= KEY_DOWN;
		static constexpr int KEY_NEWLINE		= 10;
		static constexpr int KEY_ESCAPE			= 27;
		static constexpr int KEY_ERASE			= 127;
		static constexpr int KEY_DELETE			= 330;
#endif

	private:
#if defined(_WIN32) || defined(DAVSCRIPT_UNIT_TEST)
		static int m_ResizeFlag;
		static int m_ClsWidth, m_ClsHeight;
#else
		static volatile sig_atomic_t m_ResizeFlag;
#endif
	};

}
