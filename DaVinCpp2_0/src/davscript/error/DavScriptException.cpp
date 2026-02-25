#include "DavScriptException.h"

namespace davincpp::davscript
{
    DavScriptException::DavScriptException(const std::string& message)
        : std::runtime_error(message)
    { }
}
