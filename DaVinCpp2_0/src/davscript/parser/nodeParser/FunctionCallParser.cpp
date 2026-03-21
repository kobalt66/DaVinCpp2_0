#include "FunctionCallParser.h"
#include <parser/DavScriptParser.h>
#include <parser/ast/FunctionCallNode.h>
#include <parser/ast/IdentifierNode.h>
#include <parser/ast/ValueNode.h>
#include <parser/ast/VariableAccessNode.h>
#include <parser/nodeParser/IdentifierParser.h>

namespace davincpp::davscript
{
    std::shared_ptr<AstNode> FunctionCallParser::parseNode(DavScriptParser* scriptParser)
    {
        auto functionName = std::dynamic_pointer_cast<IdentifierNode>(m_IdentifierParser.parseNode(scriptParser));

        if (!scriptParser->validateSymbol(functionName, SymbolType::FUNCTION)) {
            return std::make_shared<InvalidNode>();
        }

        assert(assertSymbolAccess(scriptParser, functionName, SymbolType::FUNCTION));

        assert(assertTokenType(scriptParser, scriptParser->advanceToken(), Token(LPARAN)));

        std::vector<std::shared_ptr<AstNode>> parameters;

        while (true) {
            Token nextToken = scriptParser->peakNextToken();

            if (nextToken.getTokenType() == RPARAN) {
                break;
            }

            if (parameters.empty()) {
                assert(assertNotTokenType(scriptParser, nextToken, Token(COMMA, OPERATOR)));
            } else {
                assert(assertTokenType(scriptParser, nextToken, Token(COMMA)));
                scriptParser->advanceToken();
            }

            // todo: try parsing expression...

            Token parameterValue = scriptParser->advanceToken();

            if (checkTokenRole(parameterValue, Token(NONE, IDENTIFIER))) {
                assert(assertSymbolAccess(scriptParser, functionName, {SymbolType::VARIABLE, SymbolType::CONSTANT}));
                parameters.emplace(parameters.begin(), std::make_shared<VariableAccessNode>(parameterValue));
                continue;
            }

            if (checkTokenRole(parameterValue, Token(NONE, DATAVALUE))) {
                parameters.emplace(parameters.begin(), std::make_shared<ValueNode>(parameterValue));
                continue;
            }

            scriptParser->logUnexpectedTokenError(parameterValue, Token(NONE, NORMAL, "[\"abc\", 123, 1.23, true, {expression}, ...]"));
            assert(true);
        }

        assert(assertTokenRole(scriptParser, scriptParser->advanceToken(), Token(RPARAN)));

        return std::make_shared<FunctionCallNode>(functionName->getName(), parameters);
    }
}
