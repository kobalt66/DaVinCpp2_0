#include "CreateProjectButton.h"
#include <ui/menu/SelectionMenu.h>
#include <ui/menu/ProjectCreationWizard.h>
#include <utility>


namespace davincpp
{
    CreateProjectButton::CreateProjectButton(const std::string& displayText, std::function<void(SelectionMenu* selectionMenu, ActionButton* buttonRef)> action, const std::string& uniqueTag)
        : ActionButton(displayText, std::move(action), uniqueTag)
    { }


    void CreateProjectButton::onInteraction(SelectionMenu* selectionMenu)
    {
        std::shared_ptr<ProjectCreationWizard> projectCreationWizard = selectionMenu->getMenuPage<ProjectCreationWizard>(SelectionMenu::PAGE_CREATE_PROJECT);
        std::pair<std::filesystem::path, ProjectConfig> projectData = projectCreationWizard->castProjectData();

        m_ProjectConfig = projectData.second;
        m_ProjectDirectory = projectData.first;

        m_Action(selectionMenu, this);
    }


    ProjectConfig CreateProjectButton::getProject() const
    {
        return m_ProjectConfig;
    }

    std::filesystem::path CreateProjectButton::getProjectDirectory() const
    {
        return m_ProjectDirectory;
    }
}
