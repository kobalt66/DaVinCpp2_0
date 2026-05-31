#pragma once
#include <parser/nodeParser/BaseNodeParser.h>
#include <parser/nodeParser/IdentifierParser.h>

namespace davincpp::davscript
{
class UseNodeParser final : public BaseNodeParser
{
  public:
	[[nodiscard]] std::shared_ptr<AstNode> parseNode(DavScriptParser* scriptParser) override;

  private:
	IdentifierParser m_IdentifierParser;
};
} // namespace davincpp::davscript
