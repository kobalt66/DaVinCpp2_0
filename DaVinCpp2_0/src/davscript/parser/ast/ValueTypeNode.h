#pragma once
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class ValueTypeNode : public AstNode
    {
    public:
        explicit ValueTypeNode(Token type);

        [[nodiscard]] Token getType() const;

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override { return {}; }

    private:
        Token m_Type;
    };
}
