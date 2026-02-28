#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <libraries/DavScriptStd.h>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
    struct DavScriptSymbol
    {
        int scopeDepth;
        SymbolType symbolType;
        std::function<void(DavScriptVirtualMachine*)> symbolFunction;
    };

    struct DavScriptNamespace
    {
        std::unordered_map<std::string, DavScriptSymbol> registeredSymbols;
    };

    static const std::unordered_map<std::string, DavScriptNamespace> DAVSCRIPT_LIBRARIES = {
        {"std.io", DavScriptNamespace({
                    { "print", { 0, SymbolType::FUNCTION, stdlib::io::print } }
                }
            )
        }
    };
}
