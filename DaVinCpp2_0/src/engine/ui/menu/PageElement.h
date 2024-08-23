#pragma once
#include <ui/menu/MenuElement.h>
#include <ui/menu/SelectionMenu.h>

namespace davincpp
{
	class PageElement : public MenuElement
	{
	public:
		explicit PageElement(const std::string& displayText, std::string_view pagePointer = SelectionMenu::PAGE_UNDEFINED, bool gotoPreviousPage = false, const std::string& uniqueTag = "");

		void onInteraction(SelectionMenu* selectionMenu) override;

	private:
		std::string m_PagePointer;
		bool m_GotoPreviousPage;
	};
}
