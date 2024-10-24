#include "DavScript.h"
#include <DaVinCppFileSystem.h>
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
        Content = DaVinCppFileSystem::readFile(Location);
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