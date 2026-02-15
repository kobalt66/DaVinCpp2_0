#include "DavScriptErrorFormatter.h"
#include <Console.h>

namespace davincpp::davscript
{
    std::string DavScriptErrorFormatter::generateUnexpectedTokenError(const Token& actualToken, const Token& expectedToken)
    {
        std::string info = generateErrorLocationInfo(actualToken.getDavScript(), actualToken.getTokenPosition());
        return Console::fmtTxt(
            generateErrorSeparator(info.size()),
            info,
            "Parsing error: Unexpected token: \n",
            generateErrorCodeLine(actualToken), '\n',
            "Actual token: ", actualToken.toString(), '\n',
            "Expected token: ", expectedToken.toString()
        );
    }

    std::string DavScriptErrorFormatter::generateInvalidValueTypeError(const Token& valueToken, TokenType expectedToken)
    {
        std::string info = generateErrorLocationInfo(valueToken.getDavScript(), valueToken.getTokenPosition());
        return Console::fmtTxt(
            generateErrorSeparator(info.size()),
            info,
            "Parsing error: Invalid : \n",
            generateErrorCodeLine(valueToken), '\n',
            "Actual value type: ", TOKEN_TYPE2STRING.at(valueToken.getTokenType()), '\n',
            "Expected value type: ", TOKEN_TYPE2STRING.at(expectedToken)
        );
    }

    std::string DavScriptErrorFormatter::generateErrorSeparator(size_t length)
    {
        return Console::fmtTxt("\n[", std::string(length - 2, '='), "]\n");
    }

    std::string DavScriptErrorFormatter::generateErrorLocationInfo(const DavScript& davScript, CharPosition position)
    {
        return Console::fmtTxt("Script: ", davScript.Location, " (ln: ", position.Line + 1, ", char: ", position.CharIdx + 2, "): \n");
    }

    std::string DavScriptErrorFormatter::generateErrorCodeLine(const Token& token)
    {
        DavScript targetScript = token.getDavScript();
        targetScript.loadFile();

        std::string line = targetScript.getLineByTokenPosition(token.getTokenPosition());

        if (line.empty()) {
            return "";
        }

        return Console::fmtTxt(
            '\t', line,
            '\t', std::string(token.getTokenPosition().CharIdx, ' '), std::string(token.getTokenLength(), '^')
        );
    }
}
