#pragma once
#include <filesystem>
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class DirectoryEntryElement : public MenuElement
    {
    public:
        DirectoryEntryElement(const std::string& displayText, std::filesystem::path directoryPath);

        void onInteraction(SelectionMenu *selectionMenu) override { }

        [[nodiscard]] std::filesystem::path getDirectoryEntryPath() const;

    private:
        std::filesystem::path m_DirectoryEntryPath;
    };
}
