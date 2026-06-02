#include "AssignmentParser.h"
#include <parser/ast/AssignmentNode.h>
#include <parser/DavScriptParser.h>
#include <parser/ast/ValueNode.h>

namespace davincpp::davscript
{
std::shared_ptr<AstNode> AssignmentParser::parseNode(DavScriptParser* scriptParser)
{
    assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, VARIABLETYPE)));
    Token variableType = scriptParser->advanceToken();

    assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, IDENTIFIER)));
    auto variableName = std::make_shared<IdentifierNode>(scriptParser->advanceToken());

    assert(assertSymbolDoesntExist(scriptParser, variableName, SymbolType::VARIABLE));

    assert(assertTokenRole(scriptParser, scriptParser->peakNextToken(), Token(NONE, VALUETYPE)));
    std::shared_ptr<ValueTypeNode> valueType
        = std::make_shared<ValueTypeNode>(scriptParser->advanceToken());

    assert(assertTokenRole(scriptParser, scriptParser->advanceToken(), Token(EQUALS, OPERATOR)));

    // todo: allow expressions
    Token value = scriptParser->advanceToken();

    assert(assertTokenValue(scriptParser, value, valueType->getType()));

    return std::make_shared<AssignmentNode>(
        variableType, variableName->getName(), valueType, std::make_shared<ValueNode>(value));
}
}  // namespace davincpp::davscript
