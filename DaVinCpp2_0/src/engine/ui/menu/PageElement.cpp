#include "PageElement.h"

namespace davincpp
{
	PageElement::PageElement(const std::string& displayText, std::string_view pagePointer, bool gotoPreviousPage)
		: MenuElement(displayText), m_PagePointer(pagePointer), m_GotoPreviousPage(gotoPreviousPage)
	{ }


	void PageElement::onInteraction(SelectionMenu* selectionMenu)
	{
		if (m_GotoPreviousPage) {
			selectionMenu->gotoPreviousPage();
			return;
		}

		selectionMenu->switchPage(m_PagePointer);
	}
}
