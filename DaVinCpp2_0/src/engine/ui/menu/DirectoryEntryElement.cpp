#include "DirectoryEntryElement.h"
#include <utility>

namespace davincpp
{
    DirectoryEntryElement::DirectoryEntryElement(const std::string& displayText, std::filesystem::path directoryPath)
        : MenuElement(displayText), m_DirectoryEntryPath(std::move(directoryPath))
    { }


    std::filesystem::path DirectoryEntryElement::getDirectoryEntryPath() const
    {
        return m_DirectoryEntryPath;
    }

}
