#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
	class PageElement : public MenuElement
	{
	public:
		PageElement(std::string_view displayText);

		void onInteraction() override;
	};
}
