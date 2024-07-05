#pragma once
#include <ui/menu/MenuPage.h>
#include <unordered_map>

namespace davincpp
{
	class SelectionMenu
	{
	public:
		SelectionMenu() = default;

		void onLoad();
		void onRender() const;
		void onUpdate(char input);

		void switchPage(std::string_view pageTag);

	private:
		std::unordered_map<std::string, std::shared_ptr<MenuPage>> m_MenuPages;
		std::shared_ptr<MenuPage> m_CurrentPage = nullptr;
	};
}
