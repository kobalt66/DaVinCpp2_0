#pragma once
#include <Console.h>
#include <memory>
#include <error/DavScriptException.h>
#include <parser/ast/AstNode.h>

namespace davincpp::davscript
{
class CallStackNode : public AstNode
{
  public:
	void addNode(const std::shared_ptr<AstNode>& node);

	template <class T>
	[[nodiscard]] std::vector<std::shared_ptr<T>> getNodesByT() const
	{
		std::vector<std::shared_ptr<T>> nodes;

		for (const auto& node : m_CallStack) {
			if (const auto& targetNode = std::dynamic_pointer_cast<T>(node)) {
				nodes.push_back(targetNode);
			}
		}

		return nodes;
	}

	[[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& getCallStack() const;

	std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;
	[[nodiscard]] bool operator==(const AstNode& other) const override;

  protected:
	std::vector<std::shared_ptr<AstNode>> m_CallStack;
};
} // namespace davincpp::davscript
