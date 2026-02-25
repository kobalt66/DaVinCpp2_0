#pragma once
#include <parser/ast/AstNode.h>
#include <parser/ast/ValueTypeNode.h>
#include <tokens/Token.h>
#include <memory>

namespace davincpp::davscript
{
    class AssignmentNode final : public AstNode
    {
    public:
        AssignmentNode(
            Token variableType,
            Token identifier,
            std::shared_ptr<ValueTypeNode> type,
            std::shared_ptr<AstNode> value
            );

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        [[nodiscard]] Token getVariableType() const;
        [[nodiscard]] Token getIdentifier() const;
        [[nodiscard]] std::shared_ptr<ValueTypeNode> getType() const;
        [[nodiscard]] std::shared_ptr<AstNode> getValue() const;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* interpreter) override;

    private:
        Token m_VariableType;
        Token m_Identifier;
        std::shared_ptr<AstNode> m_Value;
        std::shared_ptr<ValueTypeNode> m_Type;
    };
}
