#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class ExitButton : public MenuElement
    {
    public:
        explicit ExitButton(std::string_view displayText);

        void onInteraction(SelectionMenu* selectionMenu) override;
    };
}
