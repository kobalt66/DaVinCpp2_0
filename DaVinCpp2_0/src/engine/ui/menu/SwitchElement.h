#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class SwitchElement : public MenuElement
    {
    public:
        explicit SwitchElement(const std::string& displayText);

        void onSwitchPage(SelectionMenu *selectionMenu) override;
        void onRender(bool selected) override;
        void onInteraction(SelectionMenu *selectionMenu) override;

        void setState(bool state);
        [[nodiscard]] bool getState() const;

    private:
        bool m_State = false;
    };
}
