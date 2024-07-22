#include "SelectionMenu.h"
#include <ui/menu/PageElement.h>
#include <DaVinCppExceptions.h>
#include <Console.h>

namespace davincpp
{
	void SelectionMenu::onLoad()
	{
#ifndef _WIN32
		Console::loadNcurses();
#endif

		Console::showCursor(false);
		m_MenuPages["main"] = std::make_shared<MenuPage>("D a V i n C p p  2.0\nMain Menu",
			std::make_shared<PageElement>("Test", "test"),
			std::make_shared<PageElement>("asdfasdfasdf", "asdf"),
			std::make_shared<PageElement>("alskdjfkdlsalskdjfkdlsalskdjfkdlsa", "asdf"),
			std::make_shared<PageElement>("pqowieurieowpq", "asdf")
		);

		m_MenuPages["test"] = std::make_shared<MenuPage>("This is a test page!",
			std::make_shared<PageElement>("../", "main"),
			std::make_shared<PageElement>("Test2", "asdf")
		);

		switchPage("main");
	}

	void SelectionMenu::onExecute()
	{
		do {
			if (m_ShouldShutdown) {
				break;
			}

			if (Console::clsResized()) {
#ifdef _WIN32
				Console::clear();
#else
				clear();
				Console::resizeNcurses();
#endif
				Console::resetResizeFlag();
			}

#ifdef _WIN32
			Console::onUpdate();
			onUpdate(Console::getInputKey());
			onRender();
#endif

#ifndef _WIN32
			onUpdate(Console::getInputKey());
			onRender();
#endif
		} while (true);

#ifndef _WIN32
		Console::shutDownNcurses();
#endif
	}


	void SelectionMenu::switchPage(std::string_view pageTag)
	{
		if (!m_MenuPages.contains(pageTag.data())) {
			Console::printCenteredText(Console::fmtTxt("Failed to switch pages: Page ", pageTag,"doesn't exist!"), Console::BLACK_YELLOW_PAIR, stdscr->_maxy - 1);
			return;
		}

		clear();
		m_CurrentPage = m_MenuPages.at(pageTag.data());
	}


	void SelectionMenu::onRender() const
	{
		if (m_CurrentPage == nullptr) {
			throw davincpp_error("Failed to display selection menu: current selected menu page was null!");
		}

#ifdef _WIN32
		Console::setCursor(1, 1);
		m_CurrentPage->onRender();
#else
		m_CurrentPage->onRender();
		refresh();
#endif
	}

	void SelectionMenu::onUpdate(int input)
	{
		if (input == Console::KEY_NULL) {
			return;
		}

		if (input == Console::KEY_ESCAPE) {
			m_ShouldShutdown = true;
			return;
		}

		if (input == Console::KEY_ARROW_UP) {
			m_CurrentPage->switchElement(-1);
			resetDescription();
			return;
		}

		if (input == Console::KEY_ARROW_DOWN) {
			m_CurrentPage->switchElement(1);
			resetDescription();
			return;
		}

		if (input == Console::KEY_NEWLINE) {
			m_CurrentPage->interact(this);
			resetDescription();
			return;
		}

		displayDescription(Console::fmtTxt(WRN_INVALID_INPUT, "(", Console::getInputKeyByCode(input), ") "), Console::BLACK_YELLOW_PAIR);
	}

#ifndef _WIN32
	void SelectionMenu::displayDescription(std::string_view text, int colorPair)
	{
		Console::printText(text, colorPair, stdscr->_maxy - 1);
	}

	void SelectionMenu::resetDescription()
	{
		Console::printText(" ", Console::GREEN_BLACK_PAIR, stdscr->_maxy - 1);
	}
#endif
}
