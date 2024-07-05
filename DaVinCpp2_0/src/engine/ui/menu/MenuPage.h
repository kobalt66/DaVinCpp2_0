#pragma once
#include <ui/menu/MenuElement.h>
#include <DaVinCppExceptions.h>
#include <Console.h>
#include <memory>
#include <vector>

namespace davincpp
{
	class MenuPage
	{
	public:
		template<class ...Args> MenuPage(std::string_view title, Args... args)
			: m_Title(title.data())
		{
			if (!(std::is_same_v<Args, std::shared_ptr<MenuElement>> && ...)) {
				Console::err("Failed to construct menu page: provided argument has to be of type MenuElement ptr!");
				throw core_error();
			}

			m_MenuElements.insert(m_MenuElements.begin(), { args... });

			switchElement(1);
		}

		void onRender() const;

		void switchElement(int switchDirection);
		void interact();

	private:
		void onRenderHeader() const;

	private:
		const char* m_Title;
		std::vector<std::shared_ptr<MenuElement>> m_MenuElements;

		int m_SelectedElementIdx = -1;
		std::shared_ptr<MenuElement> m_SelectedElement = nullptr;
	};
}
