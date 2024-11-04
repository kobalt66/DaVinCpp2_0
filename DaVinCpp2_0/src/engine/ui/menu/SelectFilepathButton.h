#pragma once
#include <filesystem>
#include <ui/menu/MenuElement.h>

namespace davincpp
{
    class SelectFilepathButton : public MenuElement
    {
    public:
        SelectFilepathButton(const std::string& displayText, bool showOnlyDirectories, const std::string& uniqueTag = "");

        void onRender(bool selected) override;
        void onInteraction(SelectionMenu *selectionMenu) override;

        void setFilePath(std::filesystem::path filePath);
        [[nodiscard]] std::filesystem::path getFilePath() const;

    private:
        std::filesystem::path m_FilePath;
        bool m_ShowOnlyDirectories;
    };
}
