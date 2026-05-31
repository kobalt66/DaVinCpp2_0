#pragma once
#include <parser/ast/AstNode.h>
#include <parser/ast/CallStackNode.h>
#include <tokens/Token.h>
#include <memory>

namespace davincpp::davscript
{
class FunctionNode final : public AstNode
{
  public:
	FunctionNode(Token functionType, Token functionName, Token returnType, std::shared_ptr<CallStackNode> callStack);

	[[nodiscard]] Token getFunctionType() const;
	[[nodiscard]] Token getFunctionName() const;
	[[nodiscard]] Token getReturnType() const;
	[[nodiscard]] std::shared_ptr<CallStackNode> getCallStack() const;

	std::vector<char> generateByteCode() override
	{
		return {};
	}

  private:
	Token m_FunctionType;
	Token m_FunctionName;
	Token m_ReturnType;
	std::shared_ptr<CallStackNode> m_CallStack;
};
} // namespace davincpp::davscript
