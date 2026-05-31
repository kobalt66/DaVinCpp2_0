#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <libraries/symbols/DavScriptSymbol.h>

namespace davincpp::davscript
{
struct DavScriptNamespace
{
	std::unordered_map<std::string, std::shared_ptr<DavScriptSymbol>> registeredSymbols;
};
} // namespace davincpp::davscript
