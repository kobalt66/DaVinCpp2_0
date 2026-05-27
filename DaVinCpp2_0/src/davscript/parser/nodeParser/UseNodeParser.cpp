#include "UseNodeParser.h"
#include <parser/DavScriptParser.h>
#include <parser/ast/UseNode.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> UseNodeParser::parseNode(DavScriptParser* scriptParser)
    {
        assert(assertTokenType(scriptParser, scriptParser->advanceToken(), Token(USE, KEYWORD)));

        auto namespaceNameNode = std::dynamic_pointer_cast<IdentifierNode>(m_IdentifierParser.parseNode(scriptParser));
        assert(assertValidNode(namespaceNameNode));

        return std::make_shared<UseNode>(namespaceNameNode);
    }
}
