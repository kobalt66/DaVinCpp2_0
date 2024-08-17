#include "CreateProjectButton.h"
#include <utility>

namespace davincpp
{
    CreateProjectButton::CreateProjectButton(const std::string &displayText, std::function<void(SelectionMenu *selectionMenu, ActionButton *buttonRef)> action)
        : ActionButton(displayText, std::move(action))
    { }


    Project CreateProjectButton::getProject() const
    {
        return m_Project;
    }
}
