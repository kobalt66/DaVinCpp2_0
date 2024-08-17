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
        void onUpdate(SelectionMenu *selectionMenu, int input) override;
        void interact(SelectionMenu *selectionPage) override;

        void updateDirectoryStructure();

        void setFilePathVariable(std::filesystem::path* filepathRef);
        void showOnlyDirectories(bool showOnlyDirectories);

    private:
        std::filesystem::path* m_FilepathRef = nullptr;
        std::filesystem::path m_CurrentDirectory;

        bool m_ShowOnlyDirectories = false;
    };
}
