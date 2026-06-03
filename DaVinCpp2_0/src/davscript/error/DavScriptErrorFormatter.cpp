#include "DavScriptErrorFormatter.h"

#include <Console.h>
#include <DaVinCppString.h>
#include <iomanip>
#include <sstream>

namespace davincpp::davscript {
std::string DavScriptErrorFormatter::generateUnexpectedTokenError(
    const Token& actualToken, const Token& expectedToken) {
    std::string info = generateErrorLocationInfo(
        actualToken.getDavScript(), actualToken.getTokenPosition());
    return Console::fmtTxt(generateErrorSeparator(info.size()), info,
                           "Parsing error: Unexpected token:\n",
                           generateErrorCodeLine(actualToken), '\n',
                           "Actual token: ", actualToken.toString(), '\n',
                           "Expected token: ", expectedToken.toString());
}

std::string DavScriptErrorFormatter::generateInvalidValueTypeError(
    const Token& valueToken, TokenType expectedToken) {
    std::string info = generateErrorLocationInfo(valueToken.getDavScript(),
                                                 valueToken.getTokenPosition());
    return Console::fmtTxt(
        generateErrorSeparator(info.size()), info,
        "Parsing error: Invalid value type:\n",
        generateErrorCodeLine(valueToken), '\n',
        "Actual value type: ", TOKEN_TYPE2STRING.at(valueToken.getTokenType()),
        '\n', "Expected value type: ", TOKEN_TYPE2STRING.at(expectedToken));
}

std::string DavScriptErrorFormatter::generateInaccessibleSymbolError(
    const Token& symbolToken, SymbolType symbolType) {
    std::string info = generateErrorLocationInfo(
        symbolToken.getDavScript(), symbolToken.getTokenPosition());
    return Console::fmtTxt(generateErrorSeparator(info.size()), info,
                           "Parsing error: Inaccessible symbol:\n",
                           generateErrorCodeLine(symbolToken), '\n',
                           "Symbol name: ", symbolToken.getActualValue(), '\n',
                           "Symbol type: ", SYMBOL_TYPE2STRING.at(symbolType));
}

std::string DavScriptErrorFormatter::generateNamespaceNotFoundError(
    const Token& namespaceToken) {
    std::string info = generateErrorLocationInfo(
        namespaceToken.getDavScript(), namespaceToken.getTokenPosition());
    return Console::fmtTxt(generateErrorSeparator(info.size()), info,
                           "Parsing error: Namespace not found:\n",
                           generateErrorCodeLine(namespaceToken), '\n',
                           "Namespace name: ", namespaceToken.getActualValue());
}

std::string DavScriptErrorFormatter::generateDuplicateSymbolNameError(
    const Token& symbolToken, SymbolType symbolType) {
    std::string info = generateErrorLocationInfo(
        symbolToken.getDavScript(), symbolToken.getTokenPosition());
    return Console::fmtTxt(generateErrorSeparator(info.size()), info,
                           "Parsing error: Symbol name already defined:\n",
                           generateErrorCodeLine(symbolToken), '\n',
                           "Symbol name: ", symbolToken.getActualValue(), '\n',
                           "Symbol type: ", SYMBOL_TYPE2STRING.at(symbolType));
}

std::string DavScriptErrorFormatter::generateInvalidModuleNamespaceError(
    const Token& moduleNameToken) {
    std::string info = generateErrorLocationInfo(
        moduleNameToken.getDavScript(), moduleNameToken.getTokenPosition());
    return Console::fmtTxt(
        generateErrorSeparator(info.size()), info,
        "Parsing error: Invalid module namespace: Using a namespace that is "
        "already used by a script or library:\n",
        "Module namespace: ", moduleNameToken.getActualValue());
}

std::string DavScriptErrorFormatter::generateCompilerErrorInvalidValueType(
    const Token& typeToken, ValueType expectedType) {
    std::string info = generateErrorLocationInfo(typeToken.getDavScript(),
                                                 typeToken.getTokenPosition());
    return Console::fmtTxt(
        generateErrorSeparator(info.size()), info,
        "Compiler error: Invalid type:\n", generateErrorCodeLine(typeToken),
        '\n', "Actual type: ", typeToken.getActualValue(), '\n',
        "Expected type: ", STACK_VALUE_TYPE2STRING.at(expectedType));
}

std::string
DavScriptErrorFormatter::generateCompilerErrorFoundAmbiguousFunction(
    const Token& functionName) {
    std::string info = generateErrorLocationInfo(
        functionName.getDavScript(), functionName.getTokenPosition());
    return Console::fmtTxt(generateErrorSeparator(info.size()), info,
                           "Compiler error: Found ambiguous function:\n",
                           generateErrorCodeLine(functionName), '\n',
                           "Function name: ", functionName.getActualValue());
}

std::string DavScriptErrorFormatter::generateRuntimeExitCode(uint8_t exitCode) {
    return Console::fmtTxt("\nProgram exiting with code: ",
                           static_cast<int>(exitCode));
}

std::string DavScriptErrorFormatter::generateRuntimeUnexpectedError(
    std::string_view errorMessage) {
    return Console::fmtTxt("Runtime error: Unexpected error: ", errorMessage);
}

std::string DavScriptErrorFormatter::generateRuntimeErrorInvalidOperation(
    uint8_t operation) {
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(4) << std::hex
       << static_cast<uint32_t>(operation);

    return Console::fmtTxt("Runtime error: Invalid operation: ", ss.str());
}

std::string
DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryReadAccess(
    uint32_t ptr) {
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(8) << std::hex << ptr;

    return Console::fmtTxt("Runtime error: Invalid memory read access (at ",
                           ss.str(), ")");
}

std::string
DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryWriteAccess(
    uint32_t ptr) {
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(8) << std::hex << ptr;

    return Console::fmtTxt("Runtime error: Invalid memory write access (at ",
                           ss.str(), ")");
}

std::string DavScriptErrorFormatter::generateRuntimeErrorInvalidPointerAccess(
    uint32_t ptr, std::string_view context) {
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(8) << std::hex << ptr;

    return Console::fmtTxt("Runtime error: Invalid ", context,
                           " pointer access (at ", ss.str(), ")");
}

std::string
DavScriptErrorFormatter::generateRuntimeErrorInvalidStackAccessEmptyStack() {
    return Console::fmtTxt(
        "Runtime error: Failed to access stack value: Stack is empty");
}

std::string DavScriptErrorFormatter::generateRuntimeErrorInvalidParameterValue(
    std::string_view functionName, int parameterIndex, ValueType actualType,
    std::string_view expectedType) {
    return Console::fmtTxt("Runtime error: Invalid parameter value for '",
                           functionName, "' at the ", parameterIndex,
                           ". parameter: Expected ", expectedType, ", got ",
                           STACK_VALUE_TYPE2STRING.at(actualType), "");
}

std::string DavScriptErrorFormatter::generateErrorSeparator(size_t length) {
    return Console::fmtTxt("\n[", std::string(length - 2, '='), "]\n");
}

std::string
DavScriptErrorFormatter::generateErrorLocationInfo(const DavScript& davScript,
                                                   CharPosition     position) {
    return Console::fmtTxt("Script: ", davScript.getLocation(),
                           " (ln: ", position.getLine() + 1,
                           ", char: ", position.getCharIdx() + 1, "):\n");
}

std::string DavScriptErrorFormatter::generateErrorCodeLine(const Token& token) {
    DavScript targetScript = token.getDavScript();
    targetScript.loadFile();

    std::string_view line =
        targetScript.getCodeLineByPosition(token.getTokenPosition());

    if (line.empty()) {
        return "";
    }

    std::string cleansedLine = DaVinCppString::findReplaceAll(line, "\n", "");

    std::string lineNumber =
        std::to_string(token.getTokenPosition().getLine() + 1);

    return Console::fmtTxt(
        lineNumber, " | ", cleansedLine, '\n',
        std::string(lineNumber.length(), ' '), " | ",
        std::string(token.getTokenPosition().getCharIdx(), ' '),
        std::string(token.getTokenLength(), '^'), '\n');
}
} // namespace davincpp::davscript
