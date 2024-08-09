#include "PlayButton.h"
#include "SelectionMenu.h"

namespace davincpp
{
    PlayButton::PlayButton(const std::string& displayText)
        : MenuElement(displayText)
    { }

    void PlayButton::onInteraction(SelectionMenu* selectionMenu)
    {
        selectionMenu->shouldShutDown(true);
    }
}
