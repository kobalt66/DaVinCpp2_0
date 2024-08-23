#include "ScrollSelectionElement.h"
#include <ui/menu/SelectionMenu.h>
#include <Console.h>
#include <ranges>

namespace davincpp
{
    ScrollSelectionElement::ScrollSelectionElement(const std::string &displayText, const std::vector<std::string>& options, const std::string& uniqueTag)
        : MenuElement(displayText, uniqueTag), m_Options(options)
    { }


    void ScrollSelectionElement::onSwitchPage(SelectionMenu *selectionMenu)
    {
        m_SelectedOption = 0;
    }

    void ScrollSelectionElement::onRender(bool selected)
    {
#ifdef _WIN32
        throw not_implemented(__LINE__, __FILE__);
#else
        Console::printTextMarginLR(
            Console::fmtTxt(m_DisplayText, " > "),
            m_Options.empty() ? "< >      null " : Console::fmtTxt("< >      ", m_Options.at(m_SelectedOption), " "),
            selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR,
            m_CliY,
            (stdscr->_maxx - 2) / 8,
            (stdscr->_maxx - 2) / 8
            );
#endif
    }

    void ScrollSelectionElement::onUpdate(SelectionMenu *selectionMenu, int input)
    {
        if (input == Console::KEY_ARROW_LEFT) {
            m_SelectedOption -= static_cast<int>(m_SelectedOption - 1 >= 0);
            return;
        }

        if (input == Console::KEY_ARROW_RIGHT) {
            m_SelectedOption += static_cast<int>(m_SelectedOption + 1 < m_Options.size());
            return;
        }

        SelectionMenu::displayDescription(Console::fmtTxt(SelectionMenu::WRN_INVALID_INPUT, "(", Console::getInputKeyByCode(input), ") "), Console::BLACK_YELLOW_PAIR);
    }


    void ScrollSelectionElement::setSelectedOption(const std::string& option)
    {
        auto foundOption = std::find(m_Options.begin(), m_Options.end(), option);

        if (foundOption == m_Options.end()) {
            m_SelectedOption = static_cast<int>(std::ranges::distance(m_Options.begin(), foundOption));
        }
        else {
            m_SelectedOption = 0;
        }
    }

    std::string ScrollSelectionElement::getSelectionOption() const
    {
        return m_Options[m_SelectedOption];
    }

}
