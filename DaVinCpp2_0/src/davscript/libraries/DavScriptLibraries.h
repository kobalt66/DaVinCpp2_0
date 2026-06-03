#pragma once
#include <libraries/DavScriptStd.h>
#include <libraries/symbols/DavScriptFunctionSymbol.h>
#include <libraries/symbols/DavScriptNamespace.h>
#include <string>
#include <unordered_map>

namespace davincpp::davscript {
static uint32_t GLOBAL_FUNCTION_PTR = 0;

static const DavScriptNamespace STD_IO = DavScriptNamespace(
    {{"print", std::make_shared<DavScriptFunctionSymbol>(
                   0, GLOBAL_FUNCTION_PTR++, stdlib::io::print)}});

static const std::unordered_map<std::string, DavScriptNamespace>
    DAVSCRIPT_LIBRARIES = {{"std.io", STD_IO}};
} // namespace davincpp::davscript
