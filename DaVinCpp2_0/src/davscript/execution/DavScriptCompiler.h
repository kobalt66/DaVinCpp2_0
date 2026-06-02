#pragma once
#include <execution/dto/Value.h>
#include <execution/dto/VariableScope.h>
#include <functional>
#include <libraries/DavScriptLibraries.h>
#include <memory>
#include <parser/ast/Ast.h>
#include <parser/ast/IdentifierNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
class DavScriptCompiler final
{
public:
    DavScriptCompiler(std::shared_ptr<Ast>               ast,
                      const std::vector<IdentifierNode>& usedNamespaces,
                      std::filesystem::path              projectDirectory);

    void reset();
    void compile();
    void saveByteCode();

    uint32_t           registerVariableScope(std::string_view variableName);
    [[nodiscard]] bool canAccessVariable(std::string_view variableName) const;

    [[nodiscard]] std::vector<uint8_t> determineFunctionPtr(const Token& functionName);

    void logInvalidValueTypeError(const Token& typeToken, ValueType expectedType);
    void logFoundAmbiguousFunctionError(const Token& functionName);

private:
    void useNamespace(const Token& namespaceName);

    void enterScope();
    void exitScope();

    void checkForCompilationErrors() const;

private:
    std::filesystem::path m_ProjectDirectory;

    std::shared_ptr<Ast> m_Ast;

    std::vector<VariableScope> m_VariableScopes;
    int                        m_CurrentScopeDepth = 0;

    std::vector<uint8_t> m_ByteCode;
    std::unordered_map<uint32_t,
                       std::pair<std::string, std::function<void(DavScriptVirtualMachine*)>>>
        m_RegisteredLibraryFunctions;

    std::vector<std::string> m_CompilerErrorMessages;
};
