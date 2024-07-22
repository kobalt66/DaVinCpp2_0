#include "ExitButton.h"
#include <Console.h>

namespace davincpp
{
    ExitButton::ExitButton(std::string_view displayText)
        : MenuElement(displayText)
    { }

    void ExitButton::onInteraction(SelectionMenu* selectionMenu)
    {
		Console::shutDownNcurses();
        exit(0);
    }
}
