#include "FilepathSelectionWizard.h"
#include <DaVinCppExceptions.h>
#include <DaVinCppFileSystem.h>
#include <DaVinCppString.h>
#include <DaVinCppTypes.h>
#include <ui/menu/DirectoryEntryElement.h>
#include <ui/menu/TextElement.h>
#include <ui/menu/BreakElement.h>
#include <ui/menu/PageElement.h>
#include <ui/menu/SelectionMenu.h>
#include <thread>

namespace davincpp
{
    FilepathSelectionWizard::FilepathSelectionWizard(std::string_view title)
        : MenuPage(title)
    {
#ifdef _WIN32
        throw not_implemented(__LINE__, __FILE__);
#else
        m_CurrentDirectory = "/home";
#endif
    }


    void FilepathSelectionWizard::onSwitchPage(SelectionMenu* selectionMenu)
    {
        updateDirectoryStructure();
    }

    void FilepathSelectionWizard::onUpdate(SelectionMenu* selectionMenu, int input)
    {

    }

    void FilepathSelectionWizard::interact(SelectionMenu* selectionPage)
    {
        if (auto directoryEntry = dynamic_cast<DirectoryEntryElement*>(m_SelectedElement.get())) {
            std::filesystem::path newFilepath = directoryEntry->getDirectoryEntryPath();

            if (std::string(newFilepath).find("/..") != std::string::npos) {
                newFilepath = newFilepath.parent_path().parent_path();
                m_SelectedElementIdx = 0;
                switchElement(1);
            }

            try {
                permissions(newFilepath, std::filesystem::perms::owner_all);
            } catch (std::exception& exception) {
                selectionPage->setInputControl(false);
                SelectionMenu::displayDescription(Console::fmtTxt("Failed to access file: ", exception.what()), Console::BLACK_YELLOW_PAIR);
                std::this_thread::sleep_for(sec(2));
                selectionPage->setInputControl(true);
                return;
            }

            m_CurrentDirectory = newFilepath;
            selectionPage->clearCurrentMenuPage();
            updateDirectoryStructure();
        }
    }


    void FilepathSelectionWizard::updateDirectoryStructure()
    {
        m_MenuElements.clear();
        std::pair<std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>> directoryContents = DaVinCppFileSystem::getContentsOfDirectory(m_CurrentDirectory);

        addMenuElement(std::make_shared<PageElement>("<Cancle>", SelectionMenu::PAGE_MAIN));
        addMenuElement(std::make_shared<BreakElement>());
        addMenuElement(std::make_shared<TextElement>(Console::fmtTxt("Current directory > ", m_CurrentDirectory.string(), "/ "), true, ALIGN_LEFT, 5));
        addMenuElement(std::make_shared<DirectoryEntryElement>("../", Console::fmtTxt(m_CurrentDirectory.string(), "/..")));

        for (const auto& directory : directoryContents.first) {
            std::string fileName  = directory.path().filename();
            m_MenuElements.emplace_back(std::make_shared<DirectoryEntryElement>(Console::fmtTxt(DaVinCppString::findReplaceAll(directory.path().filename().c_str(), "\"", ""), "/"), directory.path()));
        }

        if (m_ShowOnlyDirectories) {
            return;
        }

        for (const auto& file : directoryContents.second) {
            m_MenuElements.emplace_back(std::make_shared<DirectoryEntryElement>(file.path().filename(), file.path()));
        }
    }


    void FilepathSelectionWizard::setFilePathVariable(std::filesystem::path *filepathRef)
    {
        m_FilepathRef = filepathRef;
    }

    void FilepathSelectionWizard::showOnlyDirectories(bool showOnlyDirectories)
    {
        m_ShowOnlyDirectories = showOnlyDirectories;
    }
}
