#include "ModuleNodeParser.h"
#include <parser/DavScriptParser.h>
#include <parser/ast/UseNode.h>

namespace davincpp
{
std::shared_ptr<davscript::AstNode> davscript::ModuleNodeParser::parseNode(DavScriptParser* scriptParser)
{
	assert(assertTokenType(scriptParser, scriptParser->advanceToken(), Token(MODULE, KEYWORD)));

	auto moduleName = std::dynamic_pointer_cast<IdentifierNode>(m_IdentifierParser.parseNode(scriptParser));
	assert(assertValidNode(moduleName));

	return moduleName;
}
} // namespace davincpp
