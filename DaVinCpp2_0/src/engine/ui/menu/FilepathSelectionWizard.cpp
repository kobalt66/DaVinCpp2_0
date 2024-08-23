#include "FilepathSelectionWizard.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppString.h>
#include <DaVinCppTypes.h>
#include <ui/menu/DirectoryEntryElement.h>
#include <ui/menu/TextElement.h>
#include <ui/menu/BreakElement.h>
#include <ui/menu/PageElement.h>
#include <ui/menu/SelectionMenu.h>
#include <Console.h>
#include <thread>

namespace davincpp
{
    FilepathSelectionWizard::FilepathSelectionWizard(std::string_view title)
        : MenuPage(title)
    {
#ifdef _WIN32
        throw not_implemented(__LINE__, __FILE__);
#else
        m_CurrentPath = "/home";
#endif
    }


    void FilepathSelectionWizard::onSwitchPage(SelectionMenu *selectionMenu)
    {
        updateDirectoryStructure();
    }

    void FilepathSelectionWizard::interact(SelectionMenu* selectionMenu)
    {
        if (auto directoryEntry = dynamic_cast<DirectoryEntryElement*>(m_SelectedElement.get())) {
            std::filesystem::path newFilepath = directoryEntry->getDirectoryEntryPath();

            if (std::string(newFilepath).find("/..") != std::string::npos) {
                newFilepath = newFilepath.parent_path().parent_path();
                m_SelectedElementIdx = 0;
                switchElement(1);
            }

            if (!DaVinCppFileSystem::canRead(newFilepath)) {
                selectionMenu->setInputControl(false);
                SelectionMenu::displayDescription(Console::fmtTxt("Failed to access file/directory at ", newFilepath, ": You are not allowed to read at this location! "), Console::BLACK_YELLOW_PAIR);
                std::this_thread::sleep_for(sec(2));
                selectionMenu->setInputControl(true);
                return;
            }

            m_CurrentPath = newFilepath;
            selectionMenu->clearCurrentMenuPage();
            updateDirectoryStructure();
            return;
        }

        m_SelectedElement->onInteraction(selectionMenu);
    }


    void FilepathSelectionWizard::updateDirectoryStructure()
    {
        m_MenuElements.clear();
        std::pair<std::vector<std::filesystem::directory_entry>, std::vector<std::filesystem::directory_entry>> directoryContents = DaVinCppFileSystem::getContentsOfDirectory(m_CurrentPath);

        addMenuElement(std::make_shared<PageElement>("<Cancle>", SelectionMenu::PAGE_UNDEFINED, true));
        addMenuElement(std::make_shared<BreakElement>());
        addMenuElement(std::make_shared<ActionButton>("<Apply>", [this](SelectionMenu* selectionMenu, ActionButton* buttonRef) {
            *m_PathRef = m_CurrentPath;
            m_PathRef = nullptr;
            selectionMenu->gotoPreviousPage();
        }));

        addMenuElement(std::make_shared<BreakElement>());
        addMenuElement(std::make_shared<TextElement>(Console::fmtTxt("Current directory > ", m_CurrentPath.string(), "/ "), true, ALIGN_LEFT, 5));
        addMenuElement(std::make_shared<DirectoryEntryElement>("../", Console::fmtTxt(m_CurrentPath.string(), "/..")));

        for (const auto& directory : directoryContents.first) {
            std::string fileName  = directory.path().filename();
            m_MenuElements.emplace_back(std::make_shared<DirectoryEntryElement>(Console::fmtTxt(DaVinCppString::findReplaceAll(directory.path().filename().c_str(), "\"", ""), "/"), directory.path()));
        }

        if (m_ShowOnlyDirectories) {
            selectDefaultElement();
            return;
        }

        for (const auto& file : directoryContents.second) {
            m_MenuElements.emplace_back(std::make_shared<DirectoryEntryElement>(file.path().filename(), file.path()));
        }

        selectDefaultElement();
    }


    void FilepathSelectionWizard::setPathVariable(std::filesystem::path *pathRef)
    {
        m_PathRef = pathRef;

        if (m_PathRef->empty()) {
#ifdef _WIN32
            throw not_implemented(__LINE__, __FILE__);
#else
            m_CurrentPath = "/home";
#endif
            return;
        }

        m_CurrentPath = *m_PathRef;
    }

    void FilepathSelectionWizard::showOnlyDirectories(bool showOnlyDirectories)
    {
        m_ShowOnlyDirectories = showOnlyDirectories;
    }


    void FilepathSelectionWizard::selectDefaultElement()
    {
        m_SelectedElementIdx = DEFAULT_SELECTED_IDX;
        switchElement(1);
    }
}
