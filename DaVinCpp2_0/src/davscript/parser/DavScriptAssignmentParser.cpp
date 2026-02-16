#include "DavScriptAssignmentParser.h"
#include <ast/AssignmentNode.h>
#include <parser/DavScriptParser.h>
#include <ast/ValueNode.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> DavScriptAssignmentParser::parseNode(DavScriptParser* scriptParser)
    {
        assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, VARIABLETYPE)));
        Token variableType = scriptParser->advanceToken();

        assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, IDENTIFIER)));
        Token variableName = scriptParser->advanceToken();

        assert(assertTokenRole(scriptParser, scriptParser->advanceToken(), Token(LBRAKET)));
        assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, VALUETYPE)));
        std::shared_ptr<ValueTypeNode> valueType = std::make_shared<ValueTypeNode>(scriptParser->advanceToken());
        assert(assertTokenRole(scriptParser, scriptParser->advanceToken(), Token(RBRAKET)));

        assert(assertTokenRole(scriptParser, scriptParser->advanceToken(), Token( EQUALS, OPERATOR)));

        // todo: allow expressions
        Token value = scriptParser->advanceToken();

        assert(assertTokenValue(scriptParser, value, valueType->getType()));

        return std::make_shared<AssignmentNode>(
            variableType,
            variableName,
            valueType,
            std::make_shared<ValueNode>(value)
        );
    }
}
