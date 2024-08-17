#pragma once
#include <ui/menu/MenuElement.h>
#include <Console.h>
#include <memory>
#include <vector>

namespace davincpp
{
	class SelectionMenu;

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

			MenuPage::switchElement(1);
		}
		virtual ~MenuPage() = default;

		virtual void onSwitchPage(SelectionMenu* selectionMenu) { }
		virtual void onRender();
		virtual void onUpdate(SelectionMenu* selectionMenu, int input);

		virtual void switchElement(int switchDirection);
		virtual void interact(SelectionMenu* selectionPage);

		void addMenuElement(const std::shared_ptr<MenuElement>& menuElement);

		[[nodiscard]] int getStartCliY() const;

	protected:
		void onRenderHeader();

#ifndef _WIN32
		int advanceRow();
#endif

	protected:
		const char* m_Title;
		std::vector<std::shared_ptr<MenuElement>> m_MenuElements;

#ifndef _WIN32
		int m_CurrentRow = 0;
#endif

		int m_SelectedElementIdx = -1;
		std::shared_ptr<MenuElement> m_SelectedElement = nullptr;
	};
}
