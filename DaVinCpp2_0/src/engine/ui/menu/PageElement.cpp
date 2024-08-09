#include "PageElement.h"
#include "SelectionMenu.h"

namespace davincpp
{
	PageElement::PageElement(const std::string& displayText, std::string_view pagePointer)
		: MenuElement(displayText), m_PagePointer(pagePointer)
	{ }


	void PageElement::onInteraction(SelectionMenu* selectionMenu)
	{
		selectionMenu->switchPage(m_PagePointer);
	}
}
