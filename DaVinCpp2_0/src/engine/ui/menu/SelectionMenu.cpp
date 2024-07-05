#include "SelectionMenu.h"
#include <ui/menu/PageElement.h>
#include <Console.h>

namespace davincpp
{
	void SelectionMenu::onLoad()
	{
		Console::showCursor(false);
		m_MenuPages["main"] = std::make_shared<MenuPage>("D a V i n C p p  2.0\nMain Menu",
			std::shared_ptr<MenuElement>(new PageElement("Test")),
			std::shared_ptr<MenuElement>(new PageElement("asdfasdfasdf")),
			std::shared_ptr<MenuElement>(new PageElement("öalskdjfkdlsöalskdjfkdlsöalskdjfkdlsöa")),
			std::shared_ptr<MenuElement>(new PageElement("pqowieurieowpq"))
		);

		switchPage("main");
	}

	void SelectionMenu::onRender() const
	{
		if (m_CurrentPage == nullptr) {
			throw davincpp_error("Failed to display selection menu: current selected menu page was null!");
		}

		Console::setCursor(1, 1);
		m_CurrentPage->onRender();
	}

	void SelectionMenu::onUpdate(char input)
	{
		if (input == Console::KEY_ARROW_UP) {
			m_CurrentPage->switchElement(-1);
		}
		else if (input == Console::KEY_ARROW_DOWN) {
			m_CurrentPage->switchElement(1);
		}
		else if (input == Console::KEY_ENTER) {
			m_CurrentPage->interact();
		}
	}


	void SelectionMenu::switchPage(std::string_view pageTag)
	{
		if (m_MenuPages.find(pageTag.data()) == m_MenuPages.end()) {
			return;
		}

		m_CurrentPage = m_MenuPages.at(pageTag.data());
	}
}
