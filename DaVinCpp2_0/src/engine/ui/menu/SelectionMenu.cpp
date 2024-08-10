#include "SelectionMenu.h"
#include <ui/menu/PageElement.h>
#include <ui/menu/PlayButton.h>
#include <ui/menu/ExitButton.h>
#include <ui/menu/SelectProjectButton.h>
#include <ui/menu/TextFieldElement.h>
#include <ui/menu/ProjectCreationWizard.h>
#include <DaVinCppExceptions.h>
#include <Console.h>

namespace davincpp
{
	const char* SelectionMenu::PAGE_MAIN		            = "main";
	const char* SelectionMenu::PAGE_SELECT_PROJECT          = "select_project";
	const char* SelectionMenu::PAGE_CREATE_PROJECT          = "create_project";
	const char* SelectionMenu::PAGE_DELETE_PROJECT          = "delete_project";
	const char* SelectionMenu::PAGE_RENAME_PROJECT          = "rename_project";
	const char* SelectionMenu::PAGE_EDIT_PROJECT_CONFIGS	= "edit_project_config";

	const char* SelectionMenu::WRN_INVALID_INPUT			= "Invalid key input... ";

	void SelectionMenu::onLoad(const std::shared_ptr<ProjectManager>& projectManager)
	{
#ifndef _WIN32
		Console::loadNcurses();
#endif

		Console::showCursor(false);
		m_MenuPages[PAGE_MAIN] = std::make_shared<MenuPage>("D a V i n C p p  2.0\nMain Menu",
			std::make_shared<PlayButton>("Start Game"),
			std::make_shared<PageElement>("Select project", PAGE_SELECT_PROJECT),
			std::make_shared<PageElement>("Create project", PAGE_CREATE_PROJECT),
			std::make_shared<PageElement>("Delete project", PAGE_DELETE_PROJECT),
			std::make_shared<PageElement>("Rename project", PAGE_RENAME_PROJECT),
			std::make_shared<PageElement>("Edit project config", PAGE_EDIT_PROJECT_CONFIGS),
			std::make_shared<ExitButton>("Exit")
		);

		m_MenuPages[PAGE_SELECT_PROJECT] = std::make_shared<MenuPage>("Select a project",
			std::make_shared<PageElement>("../", PAGE_MAIN)
		);

		for (int i = 0; i < projectManager->getProjectList().size(); i++) {
			ProjectConfig projectConfig = projectManager->getProjectList().at(i).getProjectConfig();

			m_MenuPages[PAGE_SELECT_PROJECT]->addMenuElement(
				std::make_shared<SelectProjectButton>(projectConfig.ProjectName, projectConfig, i)
			);
		}

		m_MenuPages[PAGE_CREATE_PROJECT] = std::make_shared<ProjectCreationWizard>("Create a new project",
			std::make_shared<PageElement>("<Cancle>", PAGE_MAIN),
			std::make_shared<TextFieldElement>("Project Name", "Enter project name...", 48)
		);

		m_MenuPages[PAGE_DELETE_PROJECT] = std::make_shared<MenuPage>("Delete a project",
			std::make_shared<PageElement>("../", PAGE_MAIN)
		);

		m_MenuPages[PAGE_RENAME_PROJECT] = std::make_shared<MenuPage>("Rename a project",
			std::make_shared<PageElement>("../", PAGE_MAIN)
		);

		m_MenuPages[PAGE_EDIT_PROJECT_CONFIGS] = std::make_shared<MenuPage>("Edit project configs",
			std::make_shared<PageElement>("../", PAGE_MAIN)
		);

		switchPage(PAGE_MAIN);
	}

	void SelectionMenu::onExecute()
	{
		do {
			if (m_ShouldShutdown) {
				break;
			}

			if (Console::clsResized()) {
#ifdef _WIN32
				Console::clear();
#else
				clear();
				Console::resizeNcurses();
#endif
				Console::resetResizeFlag();
			}

#ifdef _WIN32
			Console::onUpdate();
			onUpdate(Console::getInputKey());
			onRender();
#endif

#ifndef _WIN32
			onUpdate(Console::getInputKey());
			onRender();
#endif
		} while (true);

#ifndef _WIN32
		Console::shutDownNcurses();
#endif
	}


	void SelectionMenu::switchPage(std::string_view pageTag)
	{
		if (!m_MenuPages.contains(pageTag.data())) {
			Console::printCenteredText(Console::fmtTxt("Failed to switch pages: Page ", pageTag,"doesn't exist!"), Console::BLACK_YELLOW_PAIR, stdscr->_maxy - 1);
			return;
		}

		clear();
		m_CurrentPage = m_MenuPages.at(pageTag.data());
		m_CurrentPage->onSwitchPage(this);
	}

	void SelectionMenu::shouldShutDown(bool shutDown)
	{
		m_ShouldShutdown = shutDown;
	}


	void SelectionMenu::setSelectedProjectIdx(int projectIdx)
	{
		m_SelectedProjectIdx = projectIdx;
	}

	int SelectionMenu::getSelectedProjectIdx() const
	{
		return m_SelectedProjectIdx;
	}

#ifndef _WIN32
	void SelectionMenu::displayDescription(std::string_view text, int colorPair)
	{
		Console::printText(text, colorPair, stdscr->_maxy - 1);
	}

	void SelectionMenu::resetDescription()
	{
		Console::printText(" ", Console::GREEN_BLACK_PAIR, stdscr->_maxy - 1);
	}
#endif

	void SelectionMenu::onRender() const
	{
		if (m_CurrentPage == nullptr) {
			throw davincpp_error("Failed to display selection menu: current selected menu page was null!");
		}

#ifdef _WIN32
		Console::setCursor(1, 1);
		m_CurrentPage->onRender();
#else
		m_CurrentPage->onRender();
		refresh();
#endif
	}

	void SelectionMenu::onUpdate(int input)
	{
		if (input == Console::KEY_NULL) {
			return;
		}

		if (input == Console::KEY_ARROW_UP) {
			m_CurrentPage->switchElement(-1);
			resetDescription();
			return;
		}

		if (input == Console::KEY_ARROW_DOWN) {
			m_CurrentPage->switchElement(1);
			resetDescription();
			return;
		}

		if (input == Console::KEY_NEWLINE) {
			m_CurrentPage->interact(this);
			resetDescription();
			return;
		}

		m_CurrentPage->onUpdate(this, input);
	}
}
