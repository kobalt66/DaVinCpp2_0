#include "DavScript.h"

namespace davincpp::davscript
{
    DavScript::DavScript(std::string_view scriptPath)
        : Location(scriptPath)
    {
        Name = Location.filename();
    }
}

namespace YAML
{
    bool convert<davincpp::davscript::DavScript>::decode(const Node& node, davincpp::davscript::DavScript &rhs)
    {
        rhs = davincpp::davscript::DavScript(node.as<std::string>());
        return true;
    }

}
