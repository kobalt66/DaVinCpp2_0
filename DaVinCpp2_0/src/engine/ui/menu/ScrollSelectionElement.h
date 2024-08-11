#pragma once
#include <ui/menu/MenuElement.h>
#include <vector>

namespace davincpp
{
    class ScrollSelectionElement : public MenuElement
    {
    public:
        ScrollSelectionElement(const std::string& displayText, const std::vector<std::string>& options);

        void onSwitchPage(SelectionMenu *selectionMenu) override;
        void onRender(bool selected) override;
        void onUpdate(SelectionMenu *selectionMenu, int input) override;
        void onInteraction(SelectionMenu *selectionMenu) override { }

    private:
        std::vector<std::string> m_Options;
        int m_SelectedOption = 0;
    };
}
