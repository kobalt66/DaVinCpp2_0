#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class NumberFieldElement : public MenuElement
    {
    public:
        NumberFieldElement(const std::string& displayText, int minValue, int maxValue, const std::string& uniqueTag = "");

        void onSwitchPage(SelectionMenu *selectionMenu) override;
        void onRender(bool selected) override;
        void onUpdate(SelectionMenu *selectionMenu, int input) override;
        void onInteraction(SelectionMenu *selectionMenu) override;

        void setValue(int value);
        [[nodiscard]] int getValue() const;

    private:
        int m_MinValue = 0, m_MaxValue = 0;
        int m_Value = 0;

        std::string m_EnteredTextBuffer;
    };
}
