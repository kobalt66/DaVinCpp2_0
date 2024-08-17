#pragma once
#include <ui/menu/MenuElement.h>
#include <functional>

namespace davincpp
{
    class ActionButton : public MenuElement
    {
    public:
        ActionButton(const std::string& displayText, std::function<void(SelectionMenu* selectionMenu, ActionButton* buttonRef)> action);

        void onInteraction(SelectionMenu* selectionMenu) override;

    private:
        std::function<void(SelectionMenu* selectionMenu, ActionButton* buttonRef)> m_Action;
    };
}
