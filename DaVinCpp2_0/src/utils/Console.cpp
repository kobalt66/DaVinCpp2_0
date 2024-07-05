#include "Console.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#include <iomanip>

namespace davincpp
{
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
#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
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
}
