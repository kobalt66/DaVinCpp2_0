#include "ActionButton.h"
#include <utility>

#include "SelectionMenu.h"

namespace davincpp
{
    ActionButton::ActionButton(const std::string& displayText, std::function<void(SelectionMenu* selectionMenu, ActionButton* buttonRef)> action)
        : MenuElement(displayText), m_Action(std::move(action))
    { }


    void ActionButton::onInteraction(SelectionMenu* selectionMenu)
    {
        m_Action(selectionMenu, this);
    }
}
