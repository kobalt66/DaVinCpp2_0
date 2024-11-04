#include "MenuElement.h"
#include <ui/menu/SelectionMenu.h>
#include <Console.h>
#include <utility>

namespace davincpp
{
	MenuElement::MenuElement(std::string displayText, std::string uniqueTag)
		: m_DisplayText(std::move(displayText)), m_UniqueTag(std::move(uniqueTag))
	{ }


	void MenuElement::onRender(bool selected)
	{
#ifdef _WIN32
		Console::printCenteredText(m_DisplayText, selected ? Console::GREEN_BG_BLACK_FG : Console::GREEN);
#else
		Console::printCenteredText(m_DisplayText, selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR, m_CliY);
#endif
	}

	void MenuElement::onUpdate(SelectionMenu *selectionMenu, int input)
	{
		SelectionMenu::displayDescription(Console::fmtTxt(SelectionMenu::WRN_INVALID_INPUT, "(", Console::getInputKeyByCode(input), ") "), Console::BLACK_YELLOW_PAIR);
	}


	void MenuElement::setCliY(int cliY)
	{
		m_CliY = cliY;
	}

	int MenuElement::getCliY() const
	{
		return m_CliY;
	}

	std::string_view MenuElement::getUniqueTag() const
	{
		return m_UniqueTag;
	}
}
