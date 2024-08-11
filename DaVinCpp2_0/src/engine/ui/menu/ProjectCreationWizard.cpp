#include "ProjectCreationWizard.h"
#include <ui/menu/SelectionMenu.h>

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
        m_SelectedElement->onUpdate(selectionMenu, input);
    }
}
