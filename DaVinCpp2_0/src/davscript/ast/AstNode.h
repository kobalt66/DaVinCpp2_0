#pragma once
#include <vector>

namespace davincpp::davscript
{
    class AstNode
    {
    public:
        AstNode() = default;
        virtual ~AstNode() = default;

        [[nodiscard]] virtual bool operator==(const AstNode& other) const = 0;
        [[nodiscard]] bool operator!=(const AstNode& other) const { return !(*this == other); }

        virtual std::vector<char> generateByteCode() = 0;
    };
}
