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
		void shouldShutDown(bool shutDown);

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

		const char* PAGE_MAIN				= "main";
		const char* PAGE_SELECT_PROJECT	    = "select_project";
		const char* PAGE_CREATE_PROJECT	    = "create_project";
		const char* PAGE_DELETE_PROJECT	    = "delete_project";
		const char* PAGE_RENAME_PROJECT		= "rename_project";
	};
}
