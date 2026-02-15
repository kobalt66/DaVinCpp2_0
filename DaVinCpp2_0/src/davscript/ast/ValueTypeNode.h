#pragma once
#include <ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class ValueTypeNode : public AstNode
    {
    public:
        explicit ValueTypeNode(Token type);

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        [[nodiscard]] Token getType() const;

        std::vector<char> generateByteCode() override { return {}; }

    private:
        Token m_Type;
    };
}
