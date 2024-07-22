#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
	class PageElement : public MenuElement
	{
	public:
		PageElement(std::string_view displayText, std::string_view pagePointer);

		void onInteraction(SelectionMenu* selectionMenu) override;

	private:
		std::string m_PagePointer;
	};
}
