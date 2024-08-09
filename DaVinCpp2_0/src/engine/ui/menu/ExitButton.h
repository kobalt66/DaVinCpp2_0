#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class ExitButton : public MenuElement
    {
    public:
        explicit ExitButton(const std::string& displayText);

        void onInteraction(SelectionMenu* selectionMenu) override;
    };
}
