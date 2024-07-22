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
#ifndef _WIN32
		void displayDescription(std::string_view text, int colorPair);
		void resetDescription();
#endif

	private:
		std::unordered_map<std::string, std::shared_ptr<MenuPage>> m_MenuPages;
		std::shared_ptr<MenuPage> m_CurrentPage = nullptr;

		bool m_ShouldShutdown = false;

		const char* WRN_INVALID_INPUT = "Invalid key input... ";
	};
}
