#include "MenuPage.h"
#include <ui/menu/SelectionMenu.h>
#include <DaVinCppString.h>
#include <ui/menu/BreakElement.h>
#include <ui/menu/TextElement.h>

namespace davincpp
{
	void MenuPage::onRender()
	{
#ifdef _WIN32
		onRenderHeader();
		Console::newline();
		
		for (std::shared_ptr<MenuElement> menuElement : m_MenuElements) {
			menuElement->onRender(m_SelectedElement.get() == menuElement.get());
		}

		Console::setCursor(Console::getConsoleHeight() - 1, 1);
		Console::printNChar('#', Console::getConsoleWidth(), Console::GREEN);
#else
		onRenderHeader();

		for (const std::shared_ptr<MenuElement>& menuElement : m_MenuElements) {
			menuElement->setCliY(advanceRow());
			menuElement->onRender(m_SelectedElement.get() == menuElement.get());
		}

		m_CurrentRow = 0;
#endif
	}

	void MenuPage::onUpdate(SelectionMenu* selectionMenu, int input)
	{
		SelectionMenu::displayDescription(Console::fmtTxt(SelectionMenu::WRN_INVALID_INPUT, "(", Console::getInputKeyByCode(input), ") "), Console::BLACK_YELLOW_PAIR);
	}


	void MenuPage::switchElement(int switchDirection)
	{
		while (true) {
			if (m_MenuElements.empty()) {
				return;
			}

			int newSelectedElementIdx = m_SelectedElementIdx;
			if ((m_SelectedElementIdx + switchDirection) < 0) {
				newSelectedElementIdx = static_cast<int>(m_MenuElements.size() - 1);
			}
			else if ((m_SelectedElementIdx + switchDirection) >= m_MenuElements.size()) {
				newSelectedElementIdx = 0;
			}
			else {
				newSelectedElementIdx += switchDirection;
			}

			m_SelectedElementIdx = newSelectedElementIdx;

			if (auto textElement = dynamic_cast<TextElement*>(m_MenuElements.at(newSelectedElementIdx).get())) {
				if (textElement->isSkippable()) {
					continue;
				}
			}
			else if (dynamic_cast<BreakElement*>(m_MenuElements.at(newSelectedElementIdx).get()) != nullptr) {
				continue;
			}

			m_SelectedElement = m_MenuElements.at(m_SelectedElementIdx);
			break;
		}
	}

	void MenuPage::interact(SelectionMenu* selectionMenu)
	{
		if (m_SelectedElement == nullptr) {
			return;
		}

		m_SelectedElement->onInteraction(selectionMenu);
	}


	void MenuPage::addMenuElement(const std::shared_ptr<MenuElement>& menuElement)
	{
		m_MenuElements.emplace_back(menuElement);
	}


	int MenuPage::getStartCliY() const
	{
		if (m_MenuElements.empty()) {
			return 0;
		}

		return m_MenuElements.at(0)->getCliY();
	}


	void MenuPage::onRenderHeader()
	{
#ifdef _WIN32
		std::vector<std::string> headerLines = DaVinCppString::split(m_Title, '\n');

		Console::printNChar('#', Console::getConsoleWidth(), Console::GREEN);

		for (std::string& headerLine : headerLines) {
			Console::printCenteredText(headerLine, Console::GREEN, '#', '#');
		}
		
		Console::printNChar('#', Console::getConsoleWidth(), Console::GREEN);
#else
		std::vector<std::string> headerLines = DaVinCppString::split(m_Title, '\n');

		attron(COLOR_PAIR(Console::GREEN_BLACK_PAIR));
		box(stdscr, 0, 0);
		attroff(COLOR_PAIR(Console::GREEN_BLACK_PAIR));

		for (std::string& headerLine : headerLines) {
			Console::printCenteredText(headerLine, Console::GREEN_BLACK_PAIR, advanceRow());
		}

		Console::printNChar(ACS_HLINE, Console::GREEN_BLACK_PAIR, stdscr->_maxx - 1, 1, advanceRow());
#endif
	}


#ifndef _WIN32
	int MenuPage::advanceRow()
	{
		return ++m_CurrentRow;
	}
#endif
}
