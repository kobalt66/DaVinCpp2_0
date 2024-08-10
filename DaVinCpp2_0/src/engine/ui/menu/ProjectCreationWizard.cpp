#include "ProjectCreationWizard.h"
#include <ui/menu/SelectionMenu.h>
#include <ui/menu/TextFieldElement.h>

namespace davincpp
{
    void ProjectCreationWizard::onSwitchPage(SelectionMenu *selectionMenu)
    {
        for (const std::shared_ptr<MenuElement>& menuElement : m_MenuElements) {
            menuElement->onSwitchPage(selectionMenu);
        }
    }

    void ProjectCreationWizard::onUpdate(SelectionMenu* selectionMenu, int input)
    {
        if (auto textFieldElement = dynamic_cast<TextFieldElement*>(m_SelectedElement.get())) {
            textFieldElement->onUpdate(selectionMenu, input);
            return;
        }

        SelectionMenu::displayDescription(Console::fmtTxt(SelectionMenu::WRN_INVALID_INPUT, "(", Console::getInputKeyByCode(input), ") "), Console::BLACK_YELLOW_PAIR);
    }
}
