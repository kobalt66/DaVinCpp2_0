#include "UseNodeParser.h"
#include <parser/DavScriptParser.h>
#include <parser/ast/UseNode.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> UseNodeParser::parseNode(DavScriptParser* scriptParser)
    {
        assert(assertTokenType(scriptParser, scriptParser->advanceToken(), Token(USE, KEYWORD)));

        std::string namespaceName;
        while (true) {
            assert(assertTokenType(scriptParser, scriptParser->peakNextToken(), Token(NONE, IDENTIFIER)));
            namespaceName += scriptParser->advanceToken().getActualValue();

            if (checkTokenType(scriptParser->peakNextToken(), Token(NEWLINE))) {
                break;
            }

            assert(assertTokenType(scriptParser, scriptParser->advanceToken(), Token(DOT)));
            namespaceName += ".";
        }

        return std::make_shared<UseNode>(namespaceName);
    }
}
