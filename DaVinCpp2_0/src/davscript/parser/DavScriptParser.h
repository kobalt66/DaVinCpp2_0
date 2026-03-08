#pragma once
#include <memory>
#include <vector>
#include <libraries/DavScriptLibraries.h>
#include <parser/ast/Ast.h>
#include <parser/ast/IdentifierNode.h>
#include <parser/nodeParser/AssignmentParser.h>
#include <parser/nodeParser/FunctionCallParser.h>
#include <parser/nodeParser/UseNodeParser.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptParser final
    {
    public:
        explicit DavScriptParser(DavScript scriptFile, const std::vector<Token>& tokens);

        void generateAst();

        void skipNewLines();
        void skipUntilNextLine();
        Token advanceToken();
        [[nodiscard]] Token peakNextToken(int n = 1) const;

        void enterScriptFile();

        [[nodiscard]] bool useNamespace(const Token& namespaceName);
        [[nodiscard]] bool isUsingNamespace(std::string_view namespaceName) const;
        [[nodiscard]] Token getCurrentNamespaceName() const;

        void enterScope();
        void exitScope();

        [[nodiscard]] bool registerSymbol(std::string_view symbolName, SymbolType symbolType);
        [[nodiscard]] bool validateSymbol(const std::shared_ptr<IdentifierNode>& symbolName, SymbolType symbolType) const;
        [[nodiscard]] bool isValidDefinedSymbol(std::string_view symbolName, SymbolType symbolType) const;

        [[nodiscard]] bool doesVariableAlreadyExist(const Token& variableName) const;

        void logUnexpectedTokenError(const Token& actualToken, const Token& expectedToken);
        void logInvalidValueTypeError(const Token& valueToken, TokenType expectedToken);
        void logInaccessibleSymbolError(const Token& symbolToken, SymbolType symbolType);
        void logNamespaceNotFoundError(const Token& useToken, std::string_view namespaceName);
        void logDuplicateSymbolName(const Token& symbolToken, SymbolType symbolType);

        [[nodiscard]] std::shared_ptr<Ast> getAst() const;
        [[nodiscard]] const std::vector<Token>& getUsedNamespaces() const;

    private:
        void startParsingAttempt();
        void commitParsingAttempt();
        void rollbackParsingAttempt();

        [[nodiscard]] std::shared_ptr<AstNode> parseIdentifier(const Token& nextToken);
        [[nodiscard]] std::shared_ptr<AstNode> parseKeywords(const Token& nextToken);

        void checkForErrors() const;

    private:
        std::shared_ptr<DavScriptParser> m_ParsingAttempt = nullptr;

        AssignmentParser m_AssignmentParser;
        FunctionCallParser m_FunctionCallParser;
        UseNodeParser m_UseNodeParser;
        IdentifierParser m_IdentifierParser;

        DavScript m_CurrentScriptFile;

        std::vector<std::string> m_ErrorMessages;

        int m_CurrentScopeDepth = 0;
        std::unordered_map<std::string, std::shared_ptr<DavScriptSymbol>> m_DefinedSymbols;

        std::unordered_map<std::string, DavScriptNamespace> m_RegisteredCustomNamespaces;
        std::vector<Token> m_UsedNamespaces;
        DavScriptNamespace m_CurrentNamespace;
        std::string m_CurrentNamespaceName;

        std::shared_ptr<Ast> m_Ast;
        std::vector<Token> m_Tokens;

        int m_CurrentTokenIdx = -1;

        Token m_CurrentToken;
    };
}
