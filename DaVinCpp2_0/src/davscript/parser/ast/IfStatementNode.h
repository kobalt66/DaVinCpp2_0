#pragma once
#include <parser/ast/AstNode.h>
#include <parser/ast/CallStackNode.h>
#include <parser/ast/ExpressionNode.h>
#include <memory>

namespace davincpp::davscript
{
class IfStatementNode final : AstNode
{
  public:
	IfStatementNode(std::shared_ptr<AstNode> condition, std::shared_ptr<CallStackNode> callStackNode,
	                std::shared_ptr<IfStatementNode> fallback);

	[[nodiscard]] std::shared_ptr<ExpressionNode> getCondition() const;
	[[nodiscard]] std::shared_ptr<CallStackNode> getCallStack() const;
	[[nodiscard]] std::shared_ptr<IfStatementNode> getFallback() const;

	std::vector<char> generateByteCode() override
	{
		return {};
	}

  private:
	std::shared_ptr<AstNode> m_Condition;
	std::shared_ptr<CallStackNode> m_CallStackNode;
	std::shared_ptr<IfStatementNode> m_Fallback;
};
} // namespace davincpp::davscript
