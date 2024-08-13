#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class BreakElement : public MenuElement
    {
    public:
        BreakElement();

        void onInteraction(SelectionMenu *selectionMenu) override { }
    };
}
