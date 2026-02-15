#pragma once
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptErrorFormatter final
    {
    public:
        static std::string generateUnexpectedTokenError(const Token& actualToken, const Token& expectedToken);
        static std::string generateInvalidValueTypeError(const Token& valueToken, TokenType expectedToken);

    private:
        static std::string generateErrorSeparator(size_t length);
        static std::string generateErrorLocationInfo(const DavScript& davScript, CharPosition position);
        static std::string generateErrorCodeLine(const Token& token);
    };
}
