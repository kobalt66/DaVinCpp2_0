#pragma once
#include <unordered_map>
#include <ast/CallStackNode.h>

namespace davincpp::davscript
{
    class Ast final : public CallStackNode
    {
    public:
        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

        [[nodiscard]] const std::unordered_map<std::string, int>& getFunctionIndexMap() const;
    };
}
