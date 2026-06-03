#pragma once
#include <memory>
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript {
class ExpressionNode final : public AstNode {
  public:
    ExpressionNode(std::shared_ptr<AstNode> valueA, Token operant,
                   std::shared_ptr<AstNode> valueB);

    [[nodiscard]] std::shared_ptr<AstNode> getValueA() const;
    [[nodiscard]] Token                    getOperant() const;
    [[nodiscard]] std::shared_ptr<AstNode> getValueB() const;

    std::vector<char> generateByteCode() override { return {}; }

  private:
    std::shared_ptr<AstNode> m_ValueA;
    Token                    m_Operant;
    std::shared_ptr<AstNode> m_ValueB;
};
} // namespace davincpp::davscript
