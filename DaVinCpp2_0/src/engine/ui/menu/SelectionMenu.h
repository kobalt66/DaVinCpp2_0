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
		void onExecute();

		void switchPage(std::string_view pageTag);

	private:
		void onRender() const;
		void onUpdate(int input);

	private:
		std::unordered_map<std::string, std::shared_ptr<MenuPage>> m_MenuPages;
		std::shared_ptr<MenuPage> m_CurrentPage = nullptr;
	};
}
