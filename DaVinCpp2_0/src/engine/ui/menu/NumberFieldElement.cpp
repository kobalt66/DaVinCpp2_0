#include "NumberFieldElement.h"
#include <ui/menu/SelectionMenu.h>
#include <DaVinCppNumeric.h>
#include <Console.h>
#include <numeric>

namespace davincpp
{
    NumberFieldElement::NumberFieldElement(const std::string &displayText, int minValue, int maxValue, const std::string& uniqueTag)
        : MenuElement(displayText, uniqueTag),
        m_MinValue(minValue),
        m_MaxValue(maxValue)
    { }


    void NumberFieldElement::onSwitchPage(SelectionMenu *selectionMenu)
    {
        m_Value = 0;
    }

    void NumberFieldElement::onRender(bool selected)
    {
#ifdef _WIN32
        throw not_implemented(__LINE__, __FILE__);
#else
        Console::printTextMarginLR(
            Console::fmtTxt(m_DisplayText, " > "),
            m_EnteredTextBuffer.empty() ? Console::fmtTxt("- ", m_Value, " + ") : Console::fmtTxt("(Press enter to verfiy number...)      - ", m_EnteredTextBuffer, " + "),
            selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR,
            m_CliY,
            (stdscr->_maxx - 2) / 8,
            (stdscr->_maxx - 2) / 8
            );
#endif
    }

    void NumberFieldElement::onUpdate(SelectionMenu *selectionMenu, int input)
    {
        if (input == Console::KEY_ARROW_LEFT) {
            m_Value -= static_cast<int>(m_Value - 1 >= m_MinValue);
            return;
        }

        if (input == Console::KEY_ARROW_RIGHT) {
            m_Value += static_cast<int>(m_Value + 1 <= m_MaxValue);
            return;
        }

        if (input == Console::KEY_ERASE) {
            SelectionMenu::resetDescription();

            if (m_EnteredTextBuffer.empty()) {
                return;
            }

            m_EnteredTextBuffer.pop_back();
            return;
        }

        m_EnteredTextBuffer += static_cast<char>(input);
    }

    void NumberFieldElement::onInteraction(SelectionMenu *selectionMenu)
    {
        setValue(DaVinCppNumeric::convertStringToInteger(m_EnteredTextBuffer, 0));
        m_EnteredTextBuffer.clear();
    }


    void NumberFieldElement::setValue(int value)
    {
        if (value < m_MinValue) {
            m_Value = m_MinValue;
            return;
        }

        if (value > m_MaxValue) {
            m_Value = m_MaxValue;
            return;
        }

        m_Value = value;
    }

    int NumberFieldElement::getValue() const
    {
        return m_Value;
    }
}
