#include "BaseNodeParser.h"
#include <algorithm>
#include <parser/DavScriptParser.h>

namespace davincpp::davscript
{
    bool BaseNodeParser::checkToken(const Token& actualToken, const Token& expectedToken)
    {
        return actualToken == expectedToken;
    }

    bool BaseNodeParser::checkTokenRole(const Token& actualToken, const Token& expectedToken)
    {
        return actualToken.getTokenRole() == expectedToken.getTokenRole();
    }

    bool BaseNodeParser::checkTokenType(const Token& actualToken, const Token& expectedToken)
    {
        return checkTokenRole(actualToken, expectedToken) && actualToken.getTokenType() == expectedToken.getTokenType();
    }

    bool BaseNodeParser::assertTokenValue(DavScriptParser* scriptParser, const Token& value, const Token& expectedValueType)
    {
        TokenType tokenValueType = value.getTokenType();

        TokenType expectedTokenType = NONE;
        switch (expectedValueType.getTokenType()) {
            case INTTYPE:
                expectedTokenType = tokenValueType != NUMBERINT ? INTTYPE : expectedTokenType;
                break;
            case FLOATTYPE:
                expectedTokenType = tokenValueType != NUMBERFLOAT ? FLOATTYPE : expectedTokenType;
                break;
            case STRINGTYPE:
                expectedTokenType = tokenValueType != STRING? STRINGTYPE : expectedTokenType;
                break;
            case BOOLTYPE:
                expectedTokenType = tokenValueType != TRUE && tokenValueType != FALSE ? BOOLTYPE : expectedTokenType;
                break;
            case MIXEDTYPE:
                return true;
            default:
                expectedTokenType = MIXEDTYPE;
                break;
        }

        if (expectedTokenType == NONE) {
            return true;
        }

        scriptParser->logInvalidValueTypeError(value, expectedTokenType);
        return false;
    }

    bool BaseNodeParser::assertToken(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (checkToken(actualToken, expectedToken)) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertNotToken(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (!checkToken(actualToken, expectedToken)) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertTokenRole(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (checkTokenRole(actualToken, expectedToken)) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertNotTokenRole(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (!checkTokenRole(actualToken, expectedToken)) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertTokenType(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (assertTokenRole(scriptParser, actualToken, expectedToken) && checkTokenType(actualToken, expectedToken)) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertNotTokenType(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (assertNotTokenRole(scriptParser, actualToken, expectedToken) && !checkTokenType(actualToken, expectedToken)) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertSymbolAccess(DavScriptParser* scriptParser, const std::shared_ptr<IdentifierNode>& identifierNode, SymbolType symbolType)
    {
        if (scriptParser->validateSymbol(identifierNode, symbolType)) {
            return true;
        }

        scriptParser->logInaccessibleSymbolError(identifierNode->getName(), symbolType);
        return false;
    }

    bool BaseNodeParser::assertSymbolNoAccess(DavScriptParser* scriptParser, const std::shared_ptr<IdentifierNode>& identifierNode, SymbolType symbolType)
    {
        if (!scriptParser->validateSymbol(identifierNode, symbolType)) {
            return true;
        }

        scriptParser->logInaccessibleSymbolError(identifierNode->getName(), symbolType);
        return false;
    }

    bool BaseNodeParser::assertSymbolAccess(DavScriptParser* scriptParser, const std::shared_ptr<IdentifierNode>& identifierNode, std::vector<SymbolType> symbolTypes)
    {
        return std::ranges::any_of(symbolTypes.begin(), symbolTypes.end(), [&scriptParser, &identifierNode](SymbolType type) {
            return assertSymbolAccess(scriptParser, identifierNode, type);
        });
    }

    bool BaseNodeParser::assertSymbolNoAccess(DavScriptParser* scriptParser, const std::shared_ptr<IdentifierNode>& identifierNode, std::vector<SymbolType> symbolTypes)
    {
        return std::ranges::any_of(symbolTypes.begin(), symbolTypes.end(), [&scriptParser, &identifierNode](SymbolType type) {
            return assertSymbolNoAccess(scriptParser, identifierNode, type);
        });
    }

    bool BaseNodeParser::assertSymbolDoesntExist(DavScriptParser* scriptParser, const std::shared_ptr<IdentifierNode>& identifierNode, SymbolType symbolType)
    {
        if (!scriptParser->doesVariableAlreadyExist(identifierNode->getName())) {
            return true;
        }

        scriptParser->logDuplicateSymbolName(identifierNode->getName(), symbolType);
        return false;
    }
}
