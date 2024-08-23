#pragma once
#include <Console.h>
#include <DaVinCppExceptions.h>
#include <ui/menu/MenuElement.h>
#include <unordered_map>
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

			for (const std::shared_ptr<MenuElement>& menuElement : m_MenuElements) {
				m_MenuElementsMap[menuElement->getUniqueTag().data()] = menuElement;
			}

			MenuPage::switchElement(1);
		}
		virtual ~MenuPage() = default;

		virtual void onSwitchPage(SelectionMenu* selectionMenu) { }
		virtual void onRender();
		virtual void onUpdate(SelectionMenu* selectionMenu, int input);

		virtual void switchElement(int switchDirection);
		virtual void interact(SelectionMenu* selectionMenu);

		void addMenuElement(const std::shared_ptr<MenuElement>& menuElement);

		template<class T> [[nodiscard]] std::shared_ptr<T> getMenuElementByTag(std::string_view uniqueTag) const
		{
			if (m_MenuElementsMap.find(uniqueTag.data()) == m_MenuElementsMap.end()) {
				throw davincpp_error(Console::fmtTxt("Failed to fetch menu element with unique tag '", uniqueTag, "': The element doesn't exist!"));
			}

			if (std::shared_ptr<T> menuElement = std::dynamic_pointer_cast<T>(m_MenuElementsMap.at(uniqueTag.data()))) {
				return menuElement;
			}

			throw davincpp_error(Console::fmtTxt("Failed to fetch menu element with unique tag '", uniqueTag, "': Failed to cast menu element to the desired menu element type!"));
		}

		[[nodiscard]] int getStartCliY() const;

	protected:
		void onRenderHeader();

#ifndef _WIN32
		int advanceRow();
#endif

	protected:
		const char* m_Title;
		std::unordered_map<std::string, std::shared_ptr<MenuElement>> m_MenuElementsMap;
		std::vector<std::shared_ptr<MenuElement>> m_MenuElements;

#ifndef _WIN32
		int m_CurrentRow = 0;
#endif

		int m_SelectedElementIdx = -1;
		std::shared_ptr<MenuElement> m_SelectedElement = nullptr;
	};
}
