#pragma once
#include <string>

namespace davincpp
{
	class MenuElement
	{
	public:
		explicit MenuElement(std::string_view displayText);
		virtual ~MenuElement() = default;

		void onRender(bool selected);
		virtual void onInteraction() = 0;

		void setPosition(int row, int xIdx);

	private:
		const char* m_DisplayText;
		int m_Row = 1;
		int m_Xidx = 1;
	};
}
