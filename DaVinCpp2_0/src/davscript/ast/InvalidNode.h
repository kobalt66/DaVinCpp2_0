#pragma once
#include <ast/AstNode.h>

namespace davincpp::davscript
{
    class InvalidNode final : public AstNode
    {
    public:
        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<char> generateByteCode() override;
    };
}
