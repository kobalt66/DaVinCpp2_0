#include "SelectFilepathButton.h"
#include <ui/menu/SelectionMenu.h>
#include <ui/menu/FilepathSelectionWizard.h>
#include <Console.h>
#include <utility>

namespace davincpp
{
    SelectFilepathButton::SelectFilepathButton(const std::string &displayText, bool showOnlyDirectories, const std::string& uniqueTag)
        : MenuElement(displayText, uniqueTag), m_ShowOnlyDirectories(showOnlyDirectories)
    { }


    void SelectFilepathButton::onRender(bool selected)
    {
        Console::printCenteredText(
            m_FilePath.empty() ? m_DisplayText : m_FilePath.c_str(),
            selected ? Console::BLACK_GREEN_PAIR : Console::GREEN_BLACK_PAIR,
            m_CliY
            );
    }

    void SelectFilepathButton::onInteraction(SelectionMenu* selectionMenu)
    {
        std::shared_ptr<FilepathSelectionWizard> filepathSelectionMenu = selectionMenu->getMenuPage<FilepathSelectionWizard>(SelectionMenu::PAGE_SELECT_FILE_PATH);

        filepathSelectionMenu->setPathVariable(&m_FilePath);
        filepathSelectionMenu->showOnlyDirectories(m_ShowOnlyDirectories);
        selectionMenu->switchPage(SelectionMenu::PAGE_SELECT_FILE_PATH);
    }


    void SelectFilepathButton::setFilePath(std::filesystem::path filePath)
    {
        m_FilePath = std::move(filePath);
    }

    std::filesystem::path SelectFilepathButton::getFilePath() const
    {
        return m_FilePath;
    }
}
