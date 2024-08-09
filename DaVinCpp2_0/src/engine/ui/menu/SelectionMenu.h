#pragma once
#include <ui/menu/MenuPage.h>
#include <gameprojects/ProjectManager.h>
#include <unordered_map>

namespace davincpp
{
	class SelectionMenu
	{
	public:
		SelectionMenu() = default;

		void onLoad(const std::shared_ptr<ProjectManager>& projectManager);
		void onExecute();

		void switchPage(std::string_view pageTag);
		void shouldShutDown(bool shutDown);

		void setSelectedProjectIdx(int projectIdx);
		int getSelectedProjectIdx() const;

#ifndef _WIN32
		static void displayDescription(std::string_view text, int colorPair);
		static void resetDescription();
#endif

	private:
		void onRender() const;
		void onUpdate(int input);

	public:
		static const char* PAGE_MAIN;
		static const char* PAGE_SELECT_PROJECT;
		static const char* PAGE_CREATE_PROJECT;
		static const char* PAGE_DELETE_PROJECT;
		static const char* PAGE_RENAME_PROJECT;

	private:
		std::unordered_map<std::string, std::shared_ptr<MenuPage>> m_MenuPages;
		std::shared_ptr<MenuPage> m_CurrentPage = nullptr;

		bool m_ShouldShutdown = false;

		int m_SelectedProjectIdx = 0;

		const char* WRN_INVALID_INPUT = "Invalid key input... ";
	};
}
