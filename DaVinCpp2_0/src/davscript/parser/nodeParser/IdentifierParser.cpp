#include "IdentifierParser.h"
#include <parser/DavScriptParser.h>
#include <parser/ast/IdentifierNode.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> IdentifierParser::parseNode(DavScriptParser* scriptParser)
    {
        assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, IDENTIFIER)));
        Token identifier = scriptParser->advanceToken();

        while (checkTokenType(scriptParser->peakNextToken(), Token(DOT))) {
            scriptParser->advanceToken();
            assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, IDENTIFIER)));

            Token nextIdentifier = scriptParser->advanceToken();
            identifier.setActualValue(identifier.getActualValue() + "." + nextIdentifier.getActualValue());
        }

        return std::make_shared<IdentifierNode>(identifier);
    }
}
