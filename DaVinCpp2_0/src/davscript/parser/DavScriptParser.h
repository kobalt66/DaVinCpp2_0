#pragma once
#include <memory>
#include <vector>
#include <libraries/DavScriptLibraries.h>
#include <parser/ast/Ast.h>
#include <parser/ast/IdentifierNode.h>
#include <parser/nodeParser/AssignmentParser.h>
#include <parser/nodeParser/FunctionCallParser.h>
#include <parser/nodeParser/ModuleNodeParser.h>
#include <parser/nodeParser/UseNodeParser.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
class DavScriptParser final
{
public:
    explicit DavScriptParser(DavScript                 scriptFile,
                             const std::vector<Token>& tokens,
                             bool                      root = true);

    void generateAst();
    void mapScriptsToModules(const std::filesystem::path& projectDirectory);

    void                skipNewLines();
    void                skipUntilNextLine();
    Token               advanceToken();
    [[nodiscard]] Token peakNextToken(int n = 1) const;

    [[nodiscard]] bool               useNamespace(const IdentifierNode& namespaceName);
    [[nodiscard]] bool               isUsingNamespace(std::string_view namespaceName) const;
    [[nodiscard]] IdentifierNode     getCurrentNamespaceName() const;
    [[nodiscard]] DavScriptNamespace getCurrentNamespace() const;

    void enterScope();
    void exitScope();

    /// <summary>
    /// This method tries to register a symbol defined in the current script file.
    /// <br>
    /// <br>This is done by...
    /// <br><b>1.</b> checking if the symbol is registered (<b>return false</b>)
    /// <br><b>2.</b> adding the symbol to the general '<i>definedSymbols</i>' map.
    /// <br><b>3.</b> adding the symbol to the '<i>currentNamespace</i>' object.
    /// </summary>
    [[nodiscard]] bool registerSymbol(std::string_view symbolName, SymbolType symbolType);
    [[nodiscard]] bool validateSymbol(const std::shared_ptr<IdentifierNode>& symbolName,
                                      SymbolType                             symbolType) const;
    [[nodiscard]] bool isValidDefinedSymbol(std::string_view symbolName,
                                            SymbolType       symbolType) const;

    [[nodiscard]] bool doesVariableAlreadyExist(const Token& variableName) const;

    void logUnexpectedTokenError(const Token& actualToken, const Token& expectedToken);
    void logInvalidValueTypeError(const Token& valueToken, TokenType expectedToken);
    void logInaccessibleSymbolError(const Token& symbolToken, SymbolType symbolType);
    void logNamespaceNotFoundError(const Token& namespaceToken);
    void logDuplicateSymbolNameError(const Token& symbolToken, SymbolType symbolType);
    void logInvalidModuleNamespaceError(const Token& moduleNameToken);

    [[nodiscard]] std::shared_ptr<Ast>               getAst() const;
    [[nodiscard]] const std::vector<IdentifierNode>& getUsedNamespaces() const;

private:
    [[nodiscard]] static DavScriptNamespace parseUsedScriptFile(
        const IdentifierNode& namespaceName);

    void startParsingAttempt();
    void commitParsingAttempt();
    void rollbackParsingAttempt();

    [[nodiscard]] std::shared_ptr<AstNode> parseIdentifier(const Token& nextToken);
    [[nodiscard]] std::shared_ptr<AstNode> parseKeywords(const Token& nextToken);

    void checkForErrors() const;

public:
    /// <summary>
    /// This map maps a module name to it's corresponding script file.
    /// </summary>
    static std::unordered_map<IdentifierNode, DavScript> ModuleScriptMap;

    /// <summary>
    /// This map maps a module name to the parsed scripted file ast.
    /// </summary>
    static std::unordered_map<IdentifierNode, std::shared_ptr<Ast>> ParsedScriptFilesMap;

    /// <summary>
    /// This map maps all custom registered project modules to it's corresponding namespace object.
    /// </summary>
    static std::unordered_map<IdentifierNode, DavScriptNamespace> RegisteredCustomNamespaces;

private:
    bool m_IsRoot;

    /// <summary>
    /// Is used for parsing transactions (similar to transactions in SQL, though simpler).
    /// </summary>
    std::shared_ptr<DavScriptParser> m_ParsingAttempt = nullptr;

    AssignmentParser   m_AssignmentParser;
    FunctionCallParser m_FunctionCallParser;
    UseNodeParser      m_UseNodeParser;
    ModuleNodeParser   m_ModuleNodeParser;
    IdentifierParser   m_IdentifierParser;

    DavScript m_CurrentScript;

    std::vector<std::string> m_ErrorMessages;

    int m_CurrentScopeDepth = 0;

    /// <summary>
    /// This map is for all the symbols the current script file is referencing.
    /// <br>It doesn't matter if they are internal or imported by another script.
    /// </summary>
    std::unordered_map<std::string, std::shared_ptr<DavScriptSymbol>> m_DefinedSymbols;

    /// <summary>
    /// This vector holds onto all the used modules inside the current script file.
    /// </summary>
    std::vector<IdentifierNode> m_UsedNamespaces;

    /// <summary>
    /// This namespace object only holds onto the symbols defined inside the current script file.
    /// </summary>
    DavScriptNamespace m_CurrentNamespace;

    std::shared_ptr<Ast> m_CurrentAst;

    std::vector<Token> m_Tokens;
    int                m_CurrentTokenIdx = -1;
    Token              m_CurrentToken;
};
}  // namespace davincpp::davscript
