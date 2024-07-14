#pragma once
#include <ui/menu/MenuElement.h>
#include <Console.h>
#include <memory>
#include <vector>

namespace davincpp
{
	template<typename T>
	concept MenuElementPtr = requires(T t) {
		{ std::dynamic_pointer_cast<MenuElement>(t) } -> std::convertible_to<std::shared_ptr<MenuElement>>;
	};

	class MenuPage
	{
	public:
		template<MenuElementPtr ...Args> explicit MenuPage(std::string_view title, Args... args)
			: m_Title(title.data())
		{
			m_MenuElements.insert(m_MenuElements.begin(), { args... });

			switchElement(1);
		}

		void onRender();

		void switchElement(int switchDirection);
		void interact();

	private:
		void onRenderHeader();

#ifndef _WIN32
		int advanceRow();
#endif

	private:
		const char* m_Title;
		std::vector<std::shared_ptr<MenuElement>> m_MenuElements;

#ifndef _WIN32
		int m_CurrentRow = 0;
#endif

		int m_SelectedElementIdx = -1;
		std::shared_ptr<MenuElement> m_SelectedElement = nullptr;
	};
}
