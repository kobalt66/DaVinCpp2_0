#include "DavScript.h"

namespace davincpp::davscript
{
    DavScript::DavScript(std::string_view scriptPath)
        : Location(scriptPath)
    {
        Name = Location.filename();
    }
}
