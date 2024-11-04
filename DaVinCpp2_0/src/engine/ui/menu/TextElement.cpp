#include "TextElement.h"
#include <Console.h>

namespace davincpp
{
    TextElement::TextElement(const std::string& displayText, bool skippable, TextAlign align, int margin)
        : MenuElement(displayText),
        m_Align(align),
        m_Margin(margin),
        m_Skippable(skippable)
    { }

    void TextElement::onRender(bool selected)
    {
#ifdef _WIN32
        switch (m_Align) {
            case ALIGN_LEFT:
                break;
            case ALIGN_MIDDLE:
                Console::printCenteredText(m_DisplayText, selected ? Console::GREEN_BG_BLACK_FG : Console::GREEN);
            break;
            case ALIGN_RIGHT:
                break;
        }
#else
        switch (m_Align) {
            case ALIGN_LEFT:
                Console::printTextMarginL(m_DisplayText, selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR, m_CliY, m_Margin);
                break;
            case ALIGN_MIDDLE:
                Console::printCenteredText(m_DisplayText, selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR, m_CliY);
                break;
            case ALIGN_RIGHT:
                Console::printTextMarginR(m_DisplayText, selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR, m_CliY, m_Margin);
                break;
        }
#endif
    }


    bool TextElement::isSkippable() const
    {
        return m_Skippable;
    }
}
