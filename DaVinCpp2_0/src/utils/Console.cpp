#include "Console.h"
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <sys/ioctl.h>
#endif
#include <iomanip>
#include <DaVinCppExceptions.h>

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

	void Console::loadNcurses()
	{
#ifdef _WIN32
		throw not_implemented(__LINE__, __FILE__);
#else
		initscr();
		cbreak();
		noecho();
		nodelay(stdscr, TRUE);
		keypad(stdscr, TRUE);

		start_color();
		init_pair(GREEN_BLACK_PAIR, COLOR_GREEN, COLOR_BLACK);
		init_pair(BLACK_GREEN_PAIR, COLOR_BLACK, COLOR_GREEN);
#endif
	}

	void Console::shutDownNcurses()
	{
#ifdef _WIN32
		throw not_implemented(__LINE__, __FILE__);
#else
		clear();
		refresh();
		endwin();
#endif
	}

	void Console::resizeNcurses()
	{
#ifdef _WIN32
		throw not_implemented(__LINE__, __FILE__);
#else
		std::pair<int, int> new_size = getConsoleSize();
		resize_term(new_size.second, new_size.first);

		clear();
		refresh();
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


#ifdef _WIN32
	void Console::printNChar(char c, int length, const char* color)
	{
		std::cout << color;

		for (int i = 0; i < length; i++) {
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
#else
	void Console::printCenteredText(std::string_view text, int colorPair, int cliY)
	{
		int maxx = stdscr->_maxx;
		int length = text.length();
		int padding = (maxx - length) / 2;

		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, 1, ' ', padding);
		mvprintw(cliY, padding, text.data());
		mvhline(cliY, padding + length, ' ', maxx - (padding + length));
		attroff(COLOR_PAIR(colorPair));
		refresh();
	}

	void Console::printNChar(int c, int colorPair, int length, int cliX, int cliY)
	{
		attron(COLOR_PAIR(Console::GREEN_BLACK_PAIR));
		mvhline(cliY, cliX, c, length);
		attroff(COLOR_PAIR(Console::GREEN_BLACK_PAIR));
		refresh();
	}
#endif

	void Console::clear()
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}

	void Console::newline()
	{
		std::cout << "\n";
	}


	void Console::showCursor(bool show)
	{
#ifdef _WIN32
		if (!show) {
			std::cout << "\033[?25l";
			return;
		}

		std::cout << "\033[?25h";
#else
		curs_set(show);
#endif
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

	int Console::getInputKey()
	{
#ifdef _WIN32
		if (!_kbhit()) {
			return KEY_NULL;
		}

		return static_cast<int>(_getch());
#else
		int c = getch();
		if (c == ERR) {
			return KEY_NULL;
		}

		return c;
#endif
	}


#ifndef _WIN32
	void Console::handle_resize(int sig)
	{
		m_ResizeFlag = 1;
	}
#endif
}
