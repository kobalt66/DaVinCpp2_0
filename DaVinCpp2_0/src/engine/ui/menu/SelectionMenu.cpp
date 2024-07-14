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
			std::make_shared<PageElement>("Test"),
			std::make_shared<PageElement>("asdfasdfasdf"),
			std::make_shared<PageElement>("alskdjfkdlsalskdjfkdlsalskdjfkdlsa"),
			std::make_shared<PageElement>("pqowieurieowpq")
		);

		switchPage("main");
	}

	void SelectionMenu::onExecute()
	{
		int inputChar;

		do {
#ifdef _WIN32
			Console::onUpdate();
#endif
			inputChar = Console::getInputKey();
			
			if (inputChar == Console::KEY_ESCAPE) {
#ifndef _WIN32
				Console::shutDownNcurses();
#endif
				break;
			}

			onRender();
			onUpdate(inputChar);

			if (!Console::clsResized()) {
				continue;
			}

#ifdef _WIN32
			Console::clear();
#else
			Console::resizeNcurses();
#endif

			Console::resetResizeFlag();
#ifndef _WIN32
			clear();
#endif

			onRender();
		} while (true);
	}


	void SelectionMenu::switchPage(std::string_view pageTag)
	{
		if (!m_MenuPages.contains(pageTag.data())) {
			return;
		}

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
		if (input == Console::KEY_ARROW_UP) {
			m_CurrentPage->switchElement(-1);
		}
		else if (input == Console::KEY_ARROW_DOWN) {
			m_CurrentPage->switchElement(1);
		}
		else if (input == Console::KEY_NEWLINE) {
			m_CurrentPage->interact();
		}
	}
}
