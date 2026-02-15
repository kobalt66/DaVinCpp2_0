#include "DavScriptAssignmentParser.h"
#include <ast/AssignmentNode.h>
#include <parser/DavScriptParser.h>
#include <ast/ValueNode.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> DavScriptAssignmentParser::parseNode(DavScriptParser* scriptParser)
    {
        assert(assertTokenRole(scriptParser, peakNextToken(scriptParser), Token(NONE, VARIABLETYPE)));
        Token variableType = advanceToken(scriptParser);

        assert(assertTokenRole(scriptParser, peakNextToken(scriptParser), Token(NONE, IDENTIFIER)));
        Token variableName = advanceToken(scriptParser);

        assert(assertTokenRole(scriptParser, advanceToken(scriptParser), Token(LBRAKET)));
        assert(assertTokenRole(scriptParser, peakNextToken(scriptParser), Token(NONE, VALUETYPE)));
        std::shared_ptr<ValueTypeNode> valueType = std::make_shared<ValueTypeNode>(advanceToken(scriptParser));
        assert(assertTokenRole(scriptParser, advanceToken(scriptParser), Token(RBRAKET)));

        assert(assertTokenRole(scriptParser, advanceToken(scriptParser), Token( EQUALS, OPERATOR)));

        // todo: allow expressions
        Token value = advanceToken(scriptParser);

        assert(assertTokenValue(scriptParser, value, valueType->getType()));

        return std::make_shared<AssignmentNode>(
            variableType,
            variableName,
            valueType,
            std::make_shared<ValueNode>(value)
        );
    }
}
