#pragma once
#include <filesystem>
#include <ui/menu/MenuPage.h>

namespace davincpp
{
    class FilepathSelectionWizard : public MenuPage
    {
    public:
        explicit FilepathSelectionWizard(std::string_view title);

        void onSwitchPage(SelectionMenu *selectionMenu) override;
        void interact(SelectionMenu *selectionPage) override;

        void updateDirectoryStructure();

        void setPathVariable(std::filesystem::path* pathRef);
        void showOnlyDirectories(bool showOnlyDirectories);

    private:
        void selectDefaultElement();

    private:
        const int DEFAULT_SELECTED_IDX = 3;

        std::filesystem::path* m_PathRef = nullptr;
        std::filesystem::path m_CurrentPath;

        bool m_ShowOnlyDirectories = false;
    };
}
