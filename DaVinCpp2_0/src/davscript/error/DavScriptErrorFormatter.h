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
	static std::string generateNamespaceNotFoundError(const Token& useToken);
	static std::string generateDuplicateSymbolNameError(const Token& symbolToken, SymbolType symbolType);
	static std::string generateInvalidModuleNamespaceError(const Token& moduleNameToken);

	static std::string generateCompilerErrorInvalidValueType(const Token& typeToken, ValueType expectedType);
	static std::string generateCompilerErrorFoundAmbiguousFunction(const Token& functionName);

	static std::string generateRuntimeExitCode(uint8_t exitCode);
	static std::string generateRuntimeUnexpectedError(std::string_view errorMessage);
	static std::string generateRuntimeErrorInvalidOperation(uint8_t operation);
	static std::string generateRuntimeErrorInvalidMemoryReadAccess(uint32_t ptr);
	static std::string generateRuntimeErrorInvalidMemoryWriteAccess(uint32_t ptr);
	static std::string generateRuntimeErrorInvalidPointerAccess(uint32_t ptr, std::string_view context);
	static std::string generateRuntimeErrorInvalidStackAccessEmptyStack();
	static std::string generateRuntimeErrorInvalidParameterValue(std::string_view functionName, int parameterIndex,
	                                                             ValueType actualType, std::string_view expectedType);

  private:
	static std::string generateErrorSeparator(size_t length);
	static std::string generateErrorLocationInfo(const DavScript& davScript, CharPosition position);
	static std::string generateErrorCodeLine(const Token& token);
};
} // namespace davincpp::davscript
