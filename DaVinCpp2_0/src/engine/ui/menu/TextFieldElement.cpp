#include "TextFieldElement.h"
#include <ui/menu/SelectionMenu.h>
#include <Console.h>
#include <utility>

namespace davincpp
{
    TextFieldElement::TextFieldElement(const std::string& displayText, std::string placeHolderText, int characterLimit)
        : MenuElement(displayText),
        m_PlaceHolderText(std::move(placeHolderText)),
        m_CharacterLimit(characterLimit)
    { }


    void TextFieldElement::onSwitchPage(SelectionMenu *selectionMenu)
    {
        m_EnteredText.clear();
    }

    void TextFieldElement::onRender(bool selected)
    {
#ifdef _WIN32
        throw not_implemented(__LINE__, __FILE__);
#else
        Console::printTextMarginLR(
            Console::fmtTxt(m_DisplayText, " > "),
            m_EnteredText.empty() ? m_PlaceHolderText : m_EnteredText,
            selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR,
            m_CliY,
            (stdscr->_maxx - 2) / 8,
            (stdscr->_maxx - 2) / 8
            );
#endif
    }

    void TextFieldElement::onUpdate(SelectionMenu *selectionMenu, int input)
    {
        if (input == Console::KEY_ERASE) {
            SelectionMenu::resetDescription();

            if (m_EnteredText.empty()) {
                return;
            }

            m_EnteredText.pop_back();
            return;
        }

        if (m_EnteredText.size() == m_CharacterLimit) {
            SelectionMenu::displayDescription(Console::fmtTxt("You've reached the character limit of ", m_CharacterLimit, " characters! "), Console::BLACK_YELLOW_PAIR);
            return;
        }

        SelectionMenu::resetDescription();
        m_EnteredText += static_cast<char>(input);
    }


    void TextFieldElement::setEnteredText(std::string enteredText)
    {
        if (enteredText.size() >= m_CharacterLimit) {
            enteredText.resize(static_cast<size_t>(m_CharacterLimit));
        }

        m_EnteredText = enteredText;
    }

    std::string TextFieldElement::getEnteredText() const
    {
        return m_EnteredText;
    }
}
