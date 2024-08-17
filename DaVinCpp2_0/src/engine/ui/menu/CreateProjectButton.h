#pragma once
#include <ui/menu/ActionButton.h>
#include <gameprojects/Project.h>

namespace davincpp
{
    class CreateProjectButton : public ActionButton
    {
    public:
        CreateProjectButton(const std::string& displayText, std::function<void(SelectionMenu* selectionMenu, ActionButton* buttonRef)> action);

        [[nodiscard]] Project getProject() const;

    private:
        Project m_Project;
    };
}
