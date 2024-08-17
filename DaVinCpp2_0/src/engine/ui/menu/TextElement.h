#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    enum TextAlign
    {
        ALIGN_LEFT,
        ALIGN_MIDDLE,
        ALIGN_RIGHT
    };

    class TextElement : public MenuElement
    {
    public:
        explicit TextElement(const std::string& displayText, bool skipable = true, TextAlign align = ALIGN_MIDDLE, int margin = 1);

        void onRender(bool selected) override;
        void onInteraction(SelectionMenu *selectionMenu) override { }

        [[nodiscard]] bool isSkippable() const;

    private:
        TextAlign m_Align;
        int m_Margin;
        bool m_Skippable;
    };
}
