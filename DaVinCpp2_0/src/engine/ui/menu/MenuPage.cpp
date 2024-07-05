#include "MenuPage.h"
#include <DaVinCppString.h>

namespace davincpp
{
	void MenuPage::onRender() const
	{
		onRenderHeader();
		Console::newline();
		
		for (std::shared_ptr<MenuElement> menuElement : m_MenuElements) {
			menuElement->onRender(m_SelectedElement.get() == menuElement.get());
		}

		Console::setCursor(Console::getConsoleHeight() - 1, 1);
		Console::printNChar('#', Console::getConsoleWidth(), Console::GREEN);
	}


	void MenuPage::switchElement(int switchDirection)
	{
		if (m_MenuElements.size() == 0) {
			return;
		}

		if ((m_SelectedElementIdx + switchDirection) < 0) {
			m_SelectedElementIdx = static_cast<int>(m_MenuElements.size() - 1);
		}
		else if ((m_SelectedElementIdx + switchDirection) >= m_MenuElements.size()) {
			m_SelectedElementIdx = 0;
		}
		else {
			m_SelectedElementIdx += switchDirection;
		}

		m_SelectedElement = m_MenuElements.at(m_SelectedElementIdx);
	}

	void MenuPage::interact()
	{
		if (m_SelectedElement == nullptr) {
			return;
		}

		m_SelectedElement->onInteraction();
	}


	void MenuPage::onRenderHeader() const
	{
		std::vector<std::string> headerLines = DaVinCppString::split(m_Title, '\n');

		Console::printNChar('#', Console::getConsoleWidth(), Console::GREEN);

		for (std::string& headerLine : headerLines) {
			Console::printCenteredText(headerLine, Console::GREEN, '#', '#');
		}
		
		Console::printNChar('#', Console::getConsoleWidth(), Console::GREEN);
	}
}
