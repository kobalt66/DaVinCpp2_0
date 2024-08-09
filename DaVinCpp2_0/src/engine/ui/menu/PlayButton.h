#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class PlayButton : public MenuElement
    {
    public:
        explicit PlayButton(const std::string& displayText);

        void onInteraction(SelectionMenu* selectionMenu) override;
    };
}
