#pragma once
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class ValueNode final : public AstNode
    {
    public:
        explicit ValueNode(Token value);

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        [[nodiscard]] Token getValue() const;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override { return {}; }

    private:
        Token m_Value;
    };
}
