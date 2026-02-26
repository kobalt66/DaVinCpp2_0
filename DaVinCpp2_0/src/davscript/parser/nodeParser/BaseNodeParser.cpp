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

    bool BaseNodeParser::assertTokenValue(DavScriptParser* scriptParser, const Token& value, const Token& valueType)
    {
        TokenType expectedTokenType = NONE;
        TokenType specifiedTokenValueType = valueType.getTokenType();

        if (specifiedTokenValueType == MIXEDTYPE) {
            return true;
        }

        switch (value.getTokenType()) {
            case NUMBERINT:
                expectedTokenType = specifiedTokenValueType != INTTYPE ? INTTYPE : expectedTokenType;
                break;
            case NUMBERFLOAT:
                expectedTokenType = specifiedTokenValueType != FLOATTYPE ? FLOATTYPE : expectedTokenType;
                break;
            case STRING:
                expectedTokenType = specifiedTokenValueType != STRINGTYPE ? STRINGTYPE : expectedTokenType;
                break;
            case TRUE:
            case FALSE:
                expectedTokenType = specifiedTokenValueType != BOOLTYPE ? BOOLTYPE : expectedTokenType;
                break;
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

    bool BaseNodeParser::assertSymbolAccess(DavScriptParser* scriptParser, const Token& symbolToken, SymbolType symbolType)
    {
        if (scriptParser->validateSymbol(symbolToken.getActualValue(), symbolType)) {
            return true;
        }

        scriptParser->logInaccessibleSymbolError(symbolToken, symbolType);
        return false;
    }

    bool BaseNodeParser::assertSymbolNoAccess(DavScriptParser* scriptParser, const Token& symbolToken, SymbolType symbolType)
    {
        if (!scriptParser->validateSymbol(symbolToken.getActualValue(), symbolType)) {
            return true;
        }

        scriptParser->logInaccessibleSymbolError(symbolToken, symbolType);
        return false;
    }

    bool BaseNodeParser::assertSymbolAccess(DavScriptParser* scriptParser, const Token& symbolToken, std::vector<SymbolType> symbolTypes)
    {
        return std::ranges::any_of(symbolTypes.begin(), symbolTypes.end(), [&scriptParser, &symbolToken](SymbolType type) {
            return assertSymbolAccess(scriptParser, symbolToken, type);
        });
    }

    bool BaseNodeParser::assertSymbolNoAccess(DavScriptParser* scriptParser, const Token& symbolToken, std::vector<SymbolType> symbolTypes)
    {
        return std::ranges::any_of(symbolTypes.begin(), symbolTypes.end(), [&scriptParser, &symbolToken](SymbolType type) {
            return assertSymbolNoAccess(scriptParser, symbolToken, type);
        });
    }

    bool BaseNodeParser::assertSymbolDoesntExist(DavScriptParser* scriptParser, const Token& symbolToken, SymbolType symbolType)
    {
        if (!scriptParser->doesVariableAlreadyExist(symbolToken)) {
            return true;
        }

        scriptParser->logDuplicateSymbolName(symbolToken, symbolType);
        return false;
    }
}
