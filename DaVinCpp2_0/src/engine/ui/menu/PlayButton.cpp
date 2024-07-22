#include "PlayButton.h"
#include "SelectionMenu.h"

namespace davincpp
{
    PlayButton::PlayButton(std::string_view displayText)
        : MenuElement(displayText)
    { }

    void PlayButton::onInteraction(SelectionMenu* selectionMenu)
    {
        selectionMenu->shouldShutDown(true);
    }
}
