#include "DavScript.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppString.h>
#include <utility>

namespace davincpp::davscript
{
    DavScript::DavScript(std::filesystem::path scriptPath)
        : Location(std::move(scriptPath))
    {
        Name = Location.filename();
    }


    void DavScript::loadFile()
    {
        RawContent = DaVinCppFileSystem::readFile(Location);

        RefinedContent = DaVinCppString::split(RawContent, T_NEWLINE);

        int lineCount = RawContent.at(RawContent.size() - 1) == T_NEWLINE ?
            static_cast<int>(RefinedContent.size()) :
            static_cast<int>(RefinedContent.size() - 1);

        for (int i = 0; i < lineCount; i++) {
            std::string& line = RefinedContent.at(i);
            line = line.append(1, T_NEWLINE);
        }
    }


    char DavScript::getCharByPosition(CharPosition position) const
    {
        if (atEndOfFile(position)) {
            return T_EOF;
        }

        std::string line = RefinedContent.at(position.Line);

        if (atEndOfLine(position)) {
            return line.at(line.size() - 1);
        }

        return line.at(position.CharIdx);
    }

    bool DavScript::atEndOfLine(CharPosition position) const
    {
        return position.CharIdx >= RefinedContent.at(position.Line).size();
    }

    bool DavScript::atEndOfFile(CharPosition position) const
    {
        return position.Line >= RefinedContent.size() || (position.Line == RefinedContent.size() - 1 && atEndOfLine(position));
    }
}

#ifndef DAVSCRIPT_UNIT_TEST
namespace YAML
{
    bool convert<davincpp::davscript::DavScript>::decode(const Node& node, davincpp::davscript::DavScript &rhs)
    {
        rhs = davincpp::davscript::DavScript(node.as<std::string>());
        return true;
    }

}
#endif