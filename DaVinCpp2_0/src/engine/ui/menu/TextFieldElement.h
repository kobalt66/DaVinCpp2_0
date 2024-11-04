#pragma once
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class TextFieldElement : public MenuElement
    {
    public:
        TextFieldElement(const std::string& displayText, std::string placeHolderText, int characterLimit, const std::string& uniqueTag = "");

        void onSwitchPage(SelectionMenu *selectionMenu) override;
        void onRender(bool selected) override;
        void onUpdate(SelectionMenu *selectionMenu, int input) override;
        void onInteraction(SelectionMenu *selectionMenu) override { }

        void setEnteredText(std::string enteredText);
        [[nodiscard]] std::string getEnteredText() const;

    private:
        const std::string m_PlaceHolderText;
        std::string m_EnteredText;
        int m_CharacterLimit;
    };
}
