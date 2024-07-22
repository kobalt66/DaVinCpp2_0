#include "PageElement.h"

#include "SelectionMenu.h"

namespace davincpp
{
	PageElement::PageElement(std::string_view displayText, std::string_view pagePointer)
		: MenuElement(displayText), m_PagePointer(pagePointer)
	{ }


	void PageElement::onInteraction(SelectionMenu* selectionMenu)
	{
		selectionMenu->switchPage(m_PagePointer);
	}
}
