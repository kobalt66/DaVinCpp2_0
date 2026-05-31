#pragma once
#include <parser/ast/AstNode.h>
#include <parser/ast/IdentifierNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
class UseNode final : public AstNode
{
  public:
	explicit UseNode(std::shared_ptr<IdentifierNode> namespacedName);

	[[nodiscard]] std::shared_ptr<IdentifierNode> getNamespaceName() const;

	[[nodiscard]] bool operator==(const AstNode& other) const override;

	std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

  private:
	std::shared_ptr<IdentifierNode> m_NamespacedName;
};
} // namespace davincpp::davscript
