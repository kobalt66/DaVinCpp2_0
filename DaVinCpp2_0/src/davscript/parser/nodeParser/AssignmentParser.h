#pragma once
#include <parser/nodeParser/BaseNodeParser.h>

namespace davincpp::davscript
{
class AssignmentParser final : public BaseNodeParser
{
  public:
	[[nodiscard]] std::shared_ptr<AstNode> parseNode(DavScriptParser* scriptParser) override;
};
} // namespace davincpp::davscript
