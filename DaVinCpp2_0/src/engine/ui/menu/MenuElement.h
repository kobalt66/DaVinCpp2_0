#pragma once
#include <string>

namespace davincpp
{
	class SelectionMenu;

	class MenuElement
	{
	public:
		explicit MenuElement(std::string displayText, std::string uniqueTag = "");
		virtual ~MenuElement() = default;

		virtual void onSwitchPage(SelectionMenu* selectionMenu) { }
		virtual void onRender(bool selected);
		virtual void onUpdate(SelectionMenu* selectionMenu, int input);
		virtual void onInteraction(SelectionMenu* selectionMenu) = 0;

		void setCliY(int cliY);
		[[nodiscard]] int getCliY() const;
		[[nodiscard]] std::string_view getUniqueTag() const;

	protected:
		std::string m_UniqueTag;
		std::string m_DisplayText;
		int m_CliY = 1;
		int m_Xidx = 1;
	};
}
