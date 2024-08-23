#include "PlayButton.h"
#include "SelectionMenu.h"

namespace davincpp
{
    PlayButton::PlayButton(const std::string& displayText, const std::string& uniqueTag)
        : MenuElement(displayText, uniqueTag)
    { }

    void PlayButton::onInteraction(SelectionMenu* selectionMenu)
    {
        selectionMenu->shouldShutDown(true);
    }
}
