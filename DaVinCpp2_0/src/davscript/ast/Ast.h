#pragma once
#include <unordered_map>
#include <ast/CallStackNode.h>

namespace davincpp::davscript
{
    class Ast final : public CallStackNode
    {
    public:
        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<char> generateByteCode() override;

        [[nodiscard]] int getEntryPoint() const;
        [[nodiscard]] const std::unordered_map<std::string, int>& getFunctionIndexMap() const;

    private:
        int m_EntryPoint = 0;
        std::unordered_map<std::string, int> m_FunctionIndexMap;
    };
}
