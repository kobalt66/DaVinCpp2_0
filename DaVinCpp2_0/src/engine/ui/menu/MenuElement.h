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

		void onRender(bool selected);
		virtual void onInteraction(SelectionMenu* selectionMenu) = 0;

		void setPosition(int row, int xIdx);

	private:
		std::string m_DisplayText;
		int m_Row = 1;
		int m_Xidx = 1;
	};
}
