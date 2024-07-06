#include "Console.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <csignal>
#endif
#include <iomanip>
#include <conio.h>

namespace davincpp
{
#ifdef _WIN32
	int Console::m_ResizeFlag = 0;
	int Console::m_ClsWidth = 0;
	int Console::m_ClsHeight = 0;
#else
	volatile sig_atomic_t Console::m_ResizeFlag = 0;
#endif

	void Console::onLoad()
	{
#ifdef _WIN32
#else
		signal(SIGWINCH, handle_resize);
#endif
	}

	void Console::onUpdate()
	{
#ifdef _WIN32
		std::pair<int, int> clsSize = getConsoleSize();

		if (clsSize.first != m_ClsWidth || clsSize.second != m_ClsHeight) {
			m_ResizeFlag = 1;
		}

		m_ClsWidth = clsSize.first;
		m_ClsHeight = clsSize.second;
#endif
	}


	bool Console::clsResized()
	{
		return m_ResizeFlag == 1;
	}

	void Console::resetResizeFlag()
	{
		m_ResizeFlag = 0;
	}


	void Console::printNChar(char c, int count, const char* color)
	{
		std::cout << color;

		for (int i = 0; i < count; i++) {
			std::cout << c;
		}

		std::cout << "\n";
		std::cout << "\033[0m";
	}

	void Console::printCenteredText(std::string_view text, const char* color, char firstChar, char lastChar)
	{
		int consoleWidth = Console::getConsoleWidth();
		int padding = static_cast<int>((consoleWidth + text.size() - 1) / 2);

		std::cout << color;
		std::cout << firstChar << std::setw(padding) << text.data()
			<< std::setw(consoleWidth - padding - 1)
			<< lastChar;
		std::cout << "\n";
		std::cout << "\033[0m";
	}


	void Console::clear()
	{
		std::cout << "\033[2J\033[1;1H";
	}

	void Console::newline()
	{
		std::cout << "\n";
	}


	void Console::showCursor(bool show)
	{
		if (!show) {
			std::cout << "\033[?25l";
			return;
		}

		std::cout << "\033[?25h";
	}

	void Console::setCursor(int row, int xIdx)
	{
		std::cout << "\033[" << row << ";" << xIdx << "H";
	}

	int Console::getConsoleWidth()
	{
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return w.ws_col;
#endif
	}

	int Console::getConsoleHeight()
	{
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return w.ws_row;
#endif
	}

	std::pair<int, int> Console::getConsoleSize()
	{
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return { 
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1 
		};
#else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return {
			w.ws_col,
			w.ws_row
		};
#endif
	}

	char Console::getInputKey()
	{
		if (!_kbhit()) {
			return KEY_NULL;
		}

		return _getch();
	}


#ifndef _WIN32
	void Console::handle_resize(int sig)
	{
		resize_flag = 1;
	}
#endif
}
