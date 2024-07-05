#include "MenuElement.h"
#include <Console.h>

namespace davincpp
{
	MenuElement::MenuElement(std::string_view displayText)
		: m_DisplayText(displayText.data())
	{ }


	void MenuElement::onRender(bool selected) const
	{
		Console::printCenteredText(Console::fmtTxt("> ", m_DisplayText), selected ? Console::GREEN_BG_BLACK_FG : Console::GREEN);
	}


	void MenuElement::setPosition(int row, int xIdx)
	{
		m_Row = row;
		m_Xidx = xIdx;
	}
}
