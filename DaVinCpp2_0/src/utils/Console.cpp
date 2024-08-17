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

		setlocale(LC_ALL, "");

		start_color();
		init_pair(GREEN_BLACK_PAIR, COLOR_GREEN, COLOR_BLACK);
		init_pair(BLACK_GREEN_PAIR, COLOR_BLACK, COLOR_GREEN);
		init_pair(BLACK_YELLOW_PAIR, COLOR_BLACK, COLOR_YELLOW);
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
		int length = static_cast<int>(text.length());
		int padding = (maxx - length) / 2;

		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, 1, ' ', padding);
		mvprintw(cliY, padding, text.data());
		mvhline(cliY, padding + length, ' ', maxx - (padding + length));
		attroff(COLOR_PAIR(colorPair));
		refresh();
	}

	void Console::printText(std::string_view text, int colorPair, int cliY)
	{
		int maxx = stdscr->_maxx;
		int length = static_cast<int>(text.length());

		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, 1, ' ', 1);
		mvprintw(cliY, 2, text.data());
		mvhline(cliY, length + 1, ' ', maxx - 2);
		attroff(COLOR_PAIR(colorPair));
		refresh();
	}

	void Console::printNChar(int c, int colorPair, int length, int cliX, int cliY)
	{
		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, cliX, c, length);
		attroff(COLOR_PAIR(colorPair));
		refresh();
	}

	void Console::printTextMarginL(std::string_view textLeft, int colorPair, int cliY, int marginLeft)
	{
		int maxx = stdscr->_maxx;

		int marginLeftStart = 1;
		int marginLeftEnd = marginLeft;
		int textLeftStart = marginLeftEnd + 1;

		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, marginLeftStart, ' ', marginLeftEnd);
		mvprintw(cliY, textLeftStart, textLeft.data());
		mvhline(cliY, marginLeftEnd + textLeft.size(), ' ', maxx - marginLeftEnd - textLeft.size());
		attroff(COLOR_PAIR(colorPair));
		refresh();
	}

	void Console::printTextMarginR(std::string_view textRight, int colorPair, int cliY, int marginRight)
	{
		int maxx = stdscr->_maxx;

		int marginRightStart = maxx - marginRight;
		int textRightStart = static_cast<int>(marginRightStart - textRight.size());

		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, 1, ' ', textRightStart);
		mvprintw(cliY, textRightStart, textRight.data());
		mvhline(cliY, marginRightStart, ' ', marginRight);
		attroff(COLOR_PAIR(colorPair));
		refresh();
	}

	void Console::printTextMarginLR(std::string_view textLeft, std::string_view textRight, int colorPair, int cliY, int marginLeft, int marginRight)
	{
		int maxx = stdscr->_maxx;

		int marginLeftStart = 1;
		int marginLeftEnd = marginLeft;
		int textLeftStart = marginLeftEnd + 1;

		int marginRightStart = maxx - marginRight;
		int textRightStart = static_cast<int>(marginRightStart - textRight.size());

		attron(COLOR_PAIR(colorPair));
		mvhline(cliY, marginLeftStart, ' ', marginLeftEnd);
		mvprintw(cliY, textLeftStart, textLeft.data());

		mvhline(cliY, marginLeftEnd + textLeft.size(), ' ', textRightStart - (marginLeftEnd + textLeft.size()));

		mvprintw(cliY, textRightStart, textRight.data());
		mvhline(cliY, marginRightStart, ' ', marginRight);
		attroff(COLOR_PAIR(colorPair));
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

	std::string Console::getInputKeyByCode(int keyCode)
	{
		switch (keyCode)
		{
			case KEY_NEWLINE:
				return "NL";
			case KEY_ESCAPE:
				return "ESC";
			case KEY_ARROW_UP:
				return "UP";
			case KEY_ARROW_DOWN:
				return "DOWN";
			case KEY_ARROW_LEFT:
				return "LEFT";
			case KEY_ARROW_RIGHT:
				return "RIGHT";
			default:
				return "" + std::string(1, static_cast<char>(keyCode));
		}
	}

	int Console::awaitKeyInput()
	{
#ifdef _WIN32
		return static_cast<int>(_getch());
#else
		return getchar();
#endif
	}


#ifndef _WIN32
	void Console::handle_resize(int sig)
	{
		m_ResizeFlag = 1;
	}
#endif
}
