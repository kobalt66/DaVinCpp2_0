#include "SelectionMenu.h"
#include <ui/menu/PageElement.h>
#include <ui/menu/PlayButton.h>
#include <ui/menu/ExitButton.h>
#include <ui/menu/SelectProjectButton.h>
#include <ui/menu/TextFieldElement.h>
#include <ui/menu/ScrollSelectionElement.h>
#include <ui/menu/SwitchElement.h>
#include <ui/menu/NumberFieldElement.h>
#include <ui/menu/BreakElement.h>
#include <ui/menu/CreateProjectButton.h>
#include <ui/menu/SelectFilepathButton.h>
#include <ui/menu/ProjectCreationWizard.h>
#include <ui/menu/FilepathSelectionWizard.h>
#include <DaVinCppExceptions.h>
#include <DaVinCppTypes.h>
#include <Console.h>
#include <thread>
#include <utility>

namespace davincpp
{
	const char* SelectionMenu::PAGE_UNDEFINED				= "<undefined>";
	const char* SelectionMenu::PAGE_MAIN		            = "main";
	const char* SelectionMenu::PAGE_SELECT_PROJECT          = "select_project";
	const char* SelectionMenu::PAGE_CREATE_PROJECT          = "create_project";
	const char* SelectionMenu::PAGE_DELETE_PROJECT          = "delete_project";
	const char* SelectionMenu::PAGE_RENAME_PROJECT          = "rename_project";
	const char* SelectionMenu::PAGE_EDIT_PROJECT_CONFIGS	= "edit_project_config";
	const char* SelectionMenu::PAGE_SELECT_FILE_PATH		= "select_file_path";

	const char* SelectionMenu::WRN_INVALID_INPUT			= "Invalid key input... ";

	SelectionMenu::SelectionMenu(const std::shared_ptr<ProjectManager>& projectManager)
		: m_ProjectManager(projectManager)
	{ }


	void SelectionMenu::onLoad()
	{
#ifndef _WIN32
		Console::loadNcurses();
#endif

		Console::showCursor(false);
		m_MenuPages[PAGE_MAIN] = std::make_shared<MenuPage>("D a V i n C p p  2.0\nMain Menu",
			std::make_shared<BreakElement>(),
			std::make_shared<PlayButton>("Start Game"),
			std::make_shared<BreakElement>(),
			std::make_shared<PageElement>("Select project", PAGE_SELECT_PROJECT),
			std::make_shared<PageElement>("Create project", PAGE_CREATE_PROJECT),
			std::make_shared<PageElement>("Delete project", PAGE_DELETE_PROJECT),
			std::make_shared<PageElement>("Rename project", PAGE_RENAME_PROJECT),
			std::make_shared<PageElement>("Edit project config", PAGE_EDIT_PROJECT_CONFIGS),
			std::make_shared<BreakElement>(),
			std::make_shared<ExitButton>("Exit")
		);

		m_MenuPages[PAGE_SELECT_PROJECT] = std::make_shared<MenuPage>("Select a project",
			std::make_shared<PageElement>("../", PAGE_MAIN)
		);

		for (int i = 0; i < m_ProjectManager->getProjectList().size(); i++) {
			ProjectConfig projectConfig = m_ProjectManager->getProjectList().at(i).getProjectConfig();

			m_MenuPages[PAGE_SELECT_PROJECT]->addMenuElement(
				std::make_shared<SelectProjectButton>(projectConfig.ProjectName, projectConfig, i)
			);
		}

		m_MenuPages[PAGE_CREATE_PROJECT] = std::make_shared<ProjectCreationWizard>("Create a new project",
			std::make_shared<BreakElement>(),
			std::make_shared<PageElement>("<Cancle>", PAGE_MAIN),
			std::make_shared<BreakElement>(),
			std::make_shared<BreakElement>(),
			std::make_shared<SelectFilepathButton>("Press enter to select project location...", true),
			std::make_shared<TextFieldElement>("Project name", "Enter project name...", 48),
			std::make_shared<ScrollSelectionElement>("Supported DaVinCpp verion", m_ProjectManager->getLacacyVersions()),
			std::make_shared<BreakElement>(),
			std::make_shared<SwitchElement>("Vsync"),
			std::make_shared<SwitchElement>("Show system cursor"),
			std::make_shared<BreakElement>(),
			std::make_shared<NumberFieldElement>("Resolution (width)", 0, 3000), // TODO: try to find out what the maximum client size of the screen is!
			std::make_shared<NumberFieldElement>("Resolution (height)", 0, 3000),
			std::make_shared<NumberFieldElement>("Pixel width", 0, 20),
			std::make_shared<NumberFieldElement>("Pixel height", 0, 20),
			std::make_shared<BreakElement>(),
			std::make_shared<BreakElement>(),
			std::make_shared<CreateProjectButton>("<Create project>", actionCreateProject)
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

		m_MenuPages[PAGE_SELECT_FILE_PATH] = std::make_shared<FilepathSelectionWizard>("Select a file path");

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

		if (pageTag == PAGE_MAIN) {
			m_PageInvocationHistory.clear();
		}

		clear();
		m_CurrentPage = m_MenuPages.at(pageTag.data());
		m_CurrentPage->onSwitchPage(this);
		m_PageInvocationHistory.emplace_back(m_CurrentPage);
	}

	void SelectionMenu::gotoPreviousPage()
	{
		clearCurrentMenuPage();
		m_CurrentPage->onSwitchPage(this);
		m_PageInvocationHistory.pop_back();
		m_CurrentPage = m_PageInvocationHistory.at(m_PageInvocationHistory.size() - 1);
	}

	void SelectionMenu::shouldShutDown(bool shutDown)
	{
		m_ShouldShutdown = shutDown;
	}


	void SelectionMenu::setInputControl(bool enableInput)
	{
		if (enableInput) {
			flushinp();
		}

		m_InputEnabled = enableInput;
	}

	void SelectionMenu::setSelectedProjectIdx(int projectIdx)
	{
		m_SelectedProjectIdx = projectIdx;
	}

	int SelectionMenu::getSelectedProjectIdx() const
	{
		return m_SelectedProjectIdx;
	}

	std::shared_ptr<MenuPage> SelectionMenu::getMenuPage(std::string_view pageTag)
	{
		if (!m_MenuPages.contains(pageTag.data())) {
			return nullptr;
		}

		return m_MenuPages.at(pageTag.data());
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

	void SelectionMenu::clearCurrentMenuPage() const
	{
		for (int cliY = m_CurrentPage->getStartCliY(); cliY < stdscr->_maxy - 1; cliY++) {
			Console::printNChar(' ', Console::GREEN_BLACK_PAIR, stdscr->_maxx - 1, 1, cliY);
		}
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
		if (!m_InputEnabled || input == Console::KEY_NULL) {
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


	void SelectionMenu::actionCreateProject(SelectionMenu* selectionMenu, ActionButton* buttonRef)
	{
		if (auto createProjectButton = dynamic_cast<CreateProjectButton*>(buttonRef)) {
			Project project = createProjectButton->getProject();

			try {
				selectionMenu->m_ProjectManager->initProject(project);
			}
			catch (std::runtime_error& error) {
				selectionMenu->setInputControl(false);
				displayDescription(Console::fmtTxt("Failed to created new project called '", project.getProjectConfig().ProjectName, "':", error.what(), " "), Console::BLACK_YELLOW_PAIR);
				std::this_thread::sleep_for(sec(1));
				selectionMenu->setInputControl(true);
				return;
			}

			selectionMenu->setInputControl(false);
			displayDescription(Console::fmtTxt("Created new project '", project.getProjectConfig().ProjectName, "'... "), Console::BLACK_GREEN_PAIR);
			std::this_thread::sleep_for(sec(1));
			selectionMenu->setInputControl(true);
			selectionMenu->switchPage(PAGE_MAIN);
			return;
		}

		displayDescription("Failed to create new Project: Wrong type of action button is used!", Console::BLACK_YELLOW_PAIR);
	}
}
