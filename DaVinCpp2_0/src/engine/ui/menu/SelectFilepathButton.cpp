#include "SelectFilepathButton.h"
#include <ui/menu/SelectionMenu.h>
#include <ui/menu/FilepathSelectionWizard.h>
#include <DaVinCppExceptions.h>
#include <utility>

namespace davincpp
{
    SelectFilepathButton::SelectFilepathButton(const std::string &displayText, bool showOnlyDirectories)
        : MenuElement(displayText), m_ShowOnlyDirectories(showOnlyDirectories)
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
        auto filepathSelectionMenu = dynamic_cast<FilepathSelectionWizard*>(selectionMenu->getMenuPage(SelectionMenu::PAGE_SELECT_FILE_PATH).get());

        if (filepathSelectionMenu == nullptr) {
            throw davincpp_error("Failed to fetch file path selection menu: Selection menu doesn't exist!");
        }

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
