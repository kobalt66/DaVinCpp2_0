#include "SwitchElement.h"
#include <ui/menu/SelectionMenu.h>
#include <Console.h>

namespace davincpp
{
    SwitchElement::SwitchElement(const std::string &displayText)
        : MenuElement(displayText)
    { }


    void SwitchElement::onSwitchPage(SelectionMenu *selectionMenu)
    {
        m_State = false;
    }

    void SwitchElement::onRender(bool selected)
    {
#ifdef _WIN32
        throw not_implemented(__LINE__, __FILE__);
#else
        Console::printTextMarginLR(
            Console::fmtTxt(m_DisplayText, " > "),
            m_State ? "<On>" : "<Off>",
            selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR,
            m_Row,
            (stdscr->_maxx - 2) / 8,
            (stdscr->_maxx - 2) / 8
            );
#endif
    }

    void SwitchElement::onInteraction(SelectionMenu *selectionMenu)
    {
        m_State = !m_State;
    }


    void SwitchElement::setState(bool state)
    {
        m_State = state;
    }

    bool SwitchElement::getState() const
    {
        return m_State;
    }
}
