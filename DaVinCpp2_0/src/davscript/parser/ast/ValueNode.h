#pragma once
#include <parser/ast/AstNode.h>
#include <parser/ast/ValueTypeNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
class ValueNode final : public AstNode
{
public:
    explicit ValueNode(Token value);

    [[nodiscard]] bool operator==(const AstNode& other) const override;

    [[nodiscard]] Token getValue() const;
    [[nodiscard]] Token getValueType() const;

    std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override { return {}; }
    std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler,
                                          const Token&       valueType) const;

private:
    Token m_Value;
};
}  // namespace davincpp::davscript
