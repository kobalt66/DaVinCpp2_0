#pragma once
#include <string>
#include <unordered_map>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
    struct DavScriptNamespace
    {
        std::unordered_map<std::string, std::pair<int, SymbolType>> registeredSymbols;
    };

    static const std::unordered_map<std::string, DavScriptNamespace> DAVSCRIPT_LIBRARIES = {
        {"std.io", DavScriptNamespace({
                    { "print", { 0, SymbolType::FUNCTION } }
                }
            )
        }
    };
}
