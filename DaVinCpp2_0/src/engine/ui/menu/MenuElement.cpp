#include "MenuElement.h"
#include <Console.h>

namespace davincpp
{
	MenuElement::MenuElement(std::string_view displayText)
		: m_DisplayText(displayText.data())
	{ }


	void MenuElement::onRender(bool selected)
	{
#ifdef _WIN32
		Console::printCenteredText(m_DisplayText, selected ? Console::GREEN_BG_BLACK_FG : Console::GREEN);
#else
		Console::printCenteredText(m_DisplayText, selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR, m_Row);
#endif
	}


	void MenuElement::setPosition(int row, int xIdx)
	{
		m_Row = row;
		m_Xidx = xIdx;
	}
}
