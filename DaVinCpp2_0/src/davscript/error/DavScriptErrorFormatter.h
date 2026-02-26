#pragma once
#include <execution/dto/Value.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptErrorFormatter final
    {
    public:
        static std::string generateUnexpectedTokenError(const Token& actualToken, const Token& expectedToken);
        static std::string generateInvalidValueTypeError(const Token& valueToken, TokenType expectedToken);
        static std::string generateInaccessibleSymbolError(const Token& symbolToken, SymbolType symbolType);
        static std::string generateNamespaceNotFoundError(const Token& useToken, std::string_view namespaceName);
        static std::string generateDuplicateSymbolName(const Token& symbolToken, SymbolType symbolType);

        static std::string generateCompilerErrorInvalidValueType(const Token& typeToken, ValueType expectedType);

        static std::string generateRuntimeExitCode(uint8_t exitCode);
        static std::string generateRuntimeUnexpectedError(std::string_view errorMessage);
        static std::string generateRuntimeErrorInvalidOperation(uint8_t operation);
        static std::string generateRuntimeErrorInvalidMemoryReadAccess(uint32_t ptr);
        static std::string generateRuntimeErrorInvalidMemoryWriteAccess(uint32_t ptr);

    private:
        static std::string generateErrorSeparator(size_t length);
        static std::string generateErrorLocationInfo(const DavScript& davScript, CharPosition position);
        static std::string generateErrorCodeLine(const Token& token);
    };
}
