#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class PlayButton : public MenuElement
    {
    public:
        explicit PlayButton(std::string_view displayText);

        void onInteraction(SelectionMenu* selectionMenu) override;
    };
}
