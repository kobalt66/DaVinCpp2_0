#include "FunctionCallParser.h"
#include <parser/DavScriptParser.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> FunctionCallParser::parseNode(DavScriptParser* scriptParser)
    {
        assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, IDENTIFIER)));
        Token variableType = scriptParser->advanceToken();

        return nullptr;
    }
}
