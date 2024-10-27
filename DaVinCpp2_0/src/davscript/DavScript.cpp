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

        RefinedContent = DaVinCppString::split(RawContent, '\n');

        for (std::string& line : RefinedContent) {
            line = line.append("\n");
        }
    }


    char DavScript::getCharByPosition(CharPosition position) const
    {
        if (atEndOfFile(position)) {
            return EOF_;
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