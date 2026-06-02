#pragma once
#include <string>

namespace davincpp::davscript
{
struct VariableScope
{
    std::string variableName;
    int         scopeDepth;
};
}  // namespace davincpp::davscript
