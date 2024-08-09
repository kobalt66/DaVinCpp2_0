#pragma once
#include <ui/menu/MenuElement.h>
#include <gameprojects/ProjectConfig.h>

namespace davincpp
{
    class SelectProjectButton : public MenuElement
    {
    public:
        explicit SelectProjectButton(std::string displayText, ProjectConfig& projectConfig, int projectIdx);

        void onInteraction(SelectionMenu* selectionMenu) override;

    private:
        int m_ProjectIdx;
        ProjectConfig m_TargetProjectConfig;
    };
}
