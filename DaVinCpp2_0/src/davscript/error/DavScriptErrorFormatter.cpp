#include "DavScriptErrorFormatter.h"
#include <Console.h>
#include <DaVinCppString.h>
#include <execution/DavScriptCodeExecution.h>
#include <sstream>
#include <iomanip>

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

    std::string DavScriptErrorFormatter::generateInaccessibleSymbolError(const Token& symbolToken, SymbolType symbolType)
    {
        std::string info = generateErrorLocationInfo(symbolToken.getDavScript(), symbolToken.getTokenPosition());
        return Console::fmtTxt(
            generateErrorSeparator(info.size()),
            info,
            "Parsing error: Inaccessible symbol: \n",
            generateErrorCodeLine(symbolToken), '\n',
            "Symbol name: ", symbolToken.getActualValue(), '\n',
            "Symbol type: ", SYMBOL_TYPE2STRING.at(symbolType)
        );
    }

    std::string DavScriptErrorFormatter::generateNamespaceNotFoundError(const Token& useToken, std::string_view namespaceName)
    {
        std::string info = generateErrorLocationInfo(useToken.getDavScript(), useToken.getTokenPosition());
        return Console::fmtTxt(
            generateErrorSeparator(info.size()),
            info,
            "Parsing error: Namespace not found: \n",
            generateErrorCodeLine(useToken), '\n',
            "Namespace name: ", namespaceName
        );
    }

    std::string DavScriptErrorFormatter::generateDuplicateSymbolName(const Token& symbolToken, SymbolType symbolType)
    {
        std::string info = generateErrorLocationInfo(symbolToken.getDavScript(), symbolToken.getTokenPosition());
        return Console::fmtTxt(
            generateErrorSeparator(info.size()),
            info,
            "Parsing error: Symbol name already exists somewhere else: \n",
            generateErrorCodeLine(symbolToken), '\n',
            "Symbol name: ", symbolToken.getActualValue(), '\n',
            "Symbol type: ", SYMBOL_TYPE2STRING.at(symbolType)
        );
    }

    std::string DavScriptErrorFormatter::generateCompilerErrorInvalidValueType(const Token& typeToken, ValueType expectedType)
    {
        std::string info = generateErrorLocationInfo(typeToken.getDavScript(), typeToken.getTokenPosition());
        return Console::fmtTxt(
            generateErrorSeparator(info.size()),
            info,
            "Compiler error: Invalid type: \n",
            generateErrorCodeLine(typeToken), '\n',
            "Actual type: ", typeToken.getActualValue(), '\n',
            "Expected type: ", STACK_VALUE_TYPE2STRING.at(expectedType)
        );
    }

    std::string DavScriptErrorFormatter::generateRuntimeExitCode(uint8_t exitCode)
    {
        return Console::fmtTxt("\nProgram exiting with code: ", static_cast<int>(exitCode), "\n");
    }

    std::string DavScriptErrorFormatter::generateRuntimeUnexpectedError(std::string_view errorMessage)
    {
        return Console::fmtTxt("\nRuntime error: Unexpected error: ", errorMessage, "\n");
    }

    std::string DavScriptErrorFormatter::generateRuntimeErrorInvalidOperation(uint8_t operation)
    {
        std::stringstream ss;
        ss  << "0x"
            << std::setfill('0') << std::setw(4)
            << std::hex << static_cast<uint32_t>(operation);

        return Console::fmtTxt("\nRuntime error: Invalid operation: ", ss.str(), "\n");
    }

    std::string DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryReadAccess(uint32_t ptr)
    {
        std::stringstream ss;
        ss  << "0x"
            << std::setfill('0') << std::setw(8)
            << std::hex << ptr;

        return Console::fmtTxt("\nRuntime error: Invalid memory read access (at ", ss.str(), ")\n");
    }

    std::string DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryWriteAccess(uint32_t ptr)
    {
        std::stringstream ss;
        ss  << "0x"
            << std::setfill('0') << std::setw(8)
            << std::hex << ptr;

        return Console::fmtTxt("\nRuntime error: Invalid memory write access (at ", ss.str(), ")\n");
    }

    std::string DavScriptErrorFormatter::generateErrorSeparator(size_t length)
    {
        return Console::fmtTxt("\n[", std::string(length - 2, '='), "]\n");
    }

    std::string DavScriptErrorFormatter::generateErrorLocationInfo(const DavScript& davScript, CharPosition position)
    {
        return Console::fmtTxt("Script: ", davScript.Location, " (ln: ", position.Line + 1, ", char: ", position.CharIdx + 1, "): \n");
    }

    std::string DavScriptErrorFormatter::generateErrorCodeLine(const Token& token)
    {
        DavScript targetScript = token.getDavScript();
        targetScript.loadFile();

        std::string line = targetScript.getLineByTokenPosition(token.getTokenPosition());

        if (line.empty()) {
            return "";
        }

        line = DaVinCppString::findReplaceAll(line, "\n", "");

        std::string lineNumber = std::to_string(token.getTokenPosition().Line + 1);

        return Console::fmtTxt(
            lineNumber, " | ", line, '\n',
            std::string(lineNumber.length(), ' '), " | ", std::string(token.getTokenPosition().CharIdx, ' '), std::string(token.getTokenLength(), '^'), '\n'
        );
    }
}
