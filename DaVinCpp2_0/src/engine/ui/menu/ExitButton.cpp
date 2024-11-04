#include "ExitButton.h"
#include <Console.h>

namespace davincpp
{
    ExitButton::ExitButton(const std::string& displayText)
        : MenuElement(displayText)
    { }

    void ExitButton::onInteraction(SelectionMenu* selectionMenu)
    {
		Console::shutDownNcurses();
        exit(0);
    }
}
