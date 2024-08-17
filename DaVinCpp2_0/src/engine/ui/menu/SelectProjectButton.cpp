#include "SelectProjectButton.h"
#include <ui/menu/SelectionMenu.h>
#include <DaVinCppTypes.h>
#include <thread>

namespace davincpp
{
    SelectProjectButton::SelectProjectButton(std::string displayText, ProjectConfig& projectConfig, int projectIdx)
        : MenuElement(displayText), m_TargetProjectConfig(projectConfig), m_ProjectIdx(projectIdx)
    { }


    void SelectProjectButton::onInteraction(SelectionMenu* selectionMenu)
    {
        selectionMenu->setSelectedProjectIdx(m_ProjectIdx);

        selectionMenu->setInputControl(false);
        SelectionMenu::displayDescription(Console::fmtTxt("Switched DaVinCpp Project to '", m_TargetProjectConfig.ProjectName, "'... "), Console::BLACK_GREEN_PAIR);
        std::this_thread::sleep_for(sec(1));
        selectionMenu->setInputControl(true);

        selectionMenu->switchPage(SelectionMenu::PAGE_MAIN);
    }
}
