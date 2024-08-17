#pragma once
#include <ui/menu/MenuPage.h>

namespace davincpp
{
    class ProjectCreationWizard : public MenuPage
    {
    public:
        template<MenuElementPtr ...Args> explicit ProjectCreationWizard(std::string_view title, Args... args)
            : MenuPage(title, args...)
        { }

        void onSwitchPage(SelectionMenu* selectionMenu) override;
        void onUpdate(SelectionMenu* selectionMenu, int input) override;
    };
};
