#pragma once
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript {
class VariableAccessNode final : public AstNode {
  public:
    explicit VariableAccessNode(Token variableName);

    [[nodiscard]] Token getVariableName() const;

    [[nodiscard]] bool operator==(const AstNode& other) const override;

    std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

  private:
    Token m_VariableName;
};
} // namespace davincpp::davscript
