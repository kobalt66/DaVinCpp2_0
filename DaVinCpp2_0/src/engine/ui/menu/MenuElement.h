#pragma once
#include <string>

namespace davincpp
{
	class MenuElement
	{
	public:
		MenuElement(std::string_view displayText);

		void onRender(bool selected) const;
		virtual void onInteraction() = 0;

		void setPosition(int row, int xIdx);

	private:
		const char* m_DisplayText;
		int m_Row = 1;
		int m_Xidx = 1;
	};
}
