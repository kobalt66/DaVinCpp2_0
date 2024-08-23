#pragma once
#include <ui/menu/ActionButton.h>
#include <gameprojects/ProjectConfig.h>

namespace davincpp
{
    class CreateProjectButton : public ActionButton
    {
    public:
        CreateProjectButton(const std::string& displayText, std::function<void(SelectionMenu* selectionMenu, ActionButton* buttonRef)> action, const std::string& uniqueTag = "");

        void onInteraction(SelectionMenu* selectionMenu) override;

        [[nodiscard]] ProjectConfig getProject() const;
        [[nodiscard]] std::filesystem::path getProjectDirectory() const;

    private:
        ProjectConfig m_ProjectConfig;
        std::filesystem::path m_ProjectDirectory;
    };
}
