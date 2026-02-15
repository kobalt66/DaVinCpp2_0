#pragma once
#include <DavScript.h>
#include <memory>
#include <vector>
#include <ast/Ast.h>
#include <tokens/Token.h>
#include <parser/DavScriptAssignmentParser.h>

namespace davincpp::davscript
{
    class DavScriptParser final
    {
        friend class BaseNodeParser;

    public:
        explicit DavScriptParser(const std::vector<Token>& tokens);

        void generateAst();

        [[nodiscard]] std::shared_ptr<Ast> getAst() const;

    private:
        void checkForErrors() const;

        void skipNewLines();
        void skipUntilNextLine();
        Token advanceToken();
        [[nodiscard]] Token peakNextToken() const;

        void logUnexpectedTokenError(const Token& actualToken, const Token& expectedToken);
        void logInvalidValueTypeError(const Token& valueToken, TokenType expectedToken);

    private:
        DavScriptAssignmentParser m_AssignmentParser;

        std::vector<std::string> m_ErrorMessages;

        std::shared_ptr<Ast> m_Ast;
        std::vector<Token> m_Tokens;

        int m_CurrentTokenIdx = -1;
        Token m_CurrentToken;
    };
}
