#include "BaseNodeParser.h"
#include <parser/DavScriptParser.h>

namespace davincpp::davscript
{
    void BaseNodeParser::skipNewLines(DavScriptParser* scriptParser)
    {
        scriptParser->skipNewLines();
    }

    Token BaseNodeParser::advanceToken(DavScriptParser* scriptParser)
    {
        return scriptParser->advanceToken();
    }

    Token BaseNodeParser::peakNextToken(DavScriptParser* scriptParser)
    {
        return scriptParser->peakNextToken();
    }

    bool BaseNodeParser::checkToken(const Token& actualToken, const Token& expectedToken)
    {
        return actualToken == expectedToken;
    }

    bool BaseNodeParser::checkTokenRole(const Token& actualToken, const Token& expectedToken)
    {
        return actualToken.getTokenRole() == expectedToken.getTokenRole();
    }

    bool BaseNodeParser::checkType(const Token& actualToken, const Token& expectedToken)
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
        if (actualToken == expectedToken) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertTokenRole(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (actualToken.getTokenRole() == expectedToken.getTokenRole()) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }

    bool BaseNodeParser::assertType(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken)
    {
        if (assertTokenRole(scriptParser, actualToken, expectedToken) && actualToken.getTokenType() == expectedToken.getTokenType()) {
            return true;
        }

        scriptParser->logUnexpectedTokenError(actualToken, expectedToken);
        return false;
    }
}
