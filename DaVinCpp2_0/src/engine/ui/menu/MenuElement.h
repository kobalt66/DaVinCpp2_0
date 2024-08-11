#pragma once
#include <string>

namespace davincpp
{
	class SelectionMenu;

	class MenuElement
	{
	public:
		explicit MenuElement(std::string  displayText);
		virtual ~MenuElement() = default;

		virtual void onSwitchPage(SelectionMenu* selectionMenu) { }
		virtual void onRender(bool selected);
		virtual void onUpdate(SelectionMenu* selectionMenu, int input);
		virtual void onInteraction(SelectionMenu* selectionMenu) = 0;

		void setPosition(int row, int xIdx);

	protected:
		std::string m_DisplayText;
		int m_Row = 1;
		int m_Xidx = 1;
	};
}
