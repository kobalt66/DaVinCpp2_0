#pragma once
#include <ui/menu/MenuPage.h>
#include <ui/menu/ActionButton.h>
#include <gameprojects/ProjectManager.h>
#include <unordered_map>

namespace davincpp
{
	class SelectionMenu
	{
	public:
		SelectionMenu() = default;
		explicit SelectionMenu(const std::shared_ptr<ProjectManager>& projectManager);

		void onLoad();
		void onExecute();

		void switchPage(std::string_view pageTag);
		void shouldShutDown(bool shutDown);

		void setInputControl(bool enableInput);
		void setSelectedProjectIdx(int projectIdx);
		int getSelectedProjectIdx() const;
		std::shared_ptr<MenuPage> getMenuPage(std::string_view pageTag);

#ifndef _WIN32
		static void displayDescription(std::string_view text, int colorPair);
		static void resetDescription();

		void clearCurrentMenuPage() const;
#endif

	private:
		void onRender() const;
		void onUpdate(int input);

		static void actionCreateProject(SelectionMenu* selectionMenu, ActionButton* buttonRef);

	public:
		static const char* PAGE_MAIN;
		static const char* PAGE_SELECT_PROJECT;
		static const char* PAGE_CREATE_PROJECT;
		static const char* PAGE_DELETE_PROJECT;
		static const char* PAGE_RENAME_PROJECT;
		static const char* PAGE_EDIT_PROJECT_CONFIGS;
		static const char* PAGE_SELECT_FILE_PATH;

		static const char* WRN_INVALID_INPUT;

	private:
		std::shared_ptr<ProjectManager> m_ProjectManager;

		std::unordered_map<std::string, std::shared_ptr<MenuPage>> m_MenuPages;
		std::shared_ptr<MenuPage> m_CurrentPage = nullptr;

		bool m_ShouldShutdown = false;
		bool m_InputEnabled = true;

		int m_SelectedProjectIdx = 0;
	};
}
