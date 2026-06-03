#pragma once
#include <libraries/symbols/DavScriptSymbol.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace davincpp::davscript {
struct DavScriptNamespace {
    std::unordered_map<std::string, std::shared_ptr<DavScriptSymbol>>
        registeredSymbols;
};
} // namespace davincpp::davscript
