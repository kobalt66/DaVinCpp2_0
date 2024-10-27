#pragma once
#include <DavScript.h>
#include <vector>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptLexer
    {
    public:
        explicit DavScriptLexer(DavScript davScript);

        void generateTokens();

        [[nodiscard]] const std::vector<Token>& getTokens() const;

    private:
        char advanceChar();

        [[nodiscard]] bool isSingleCharToken() const;
        [[nodiscard]] bool isOperatorToken() const;

    private:
        DavScript m_DavScript;

        std::vector<Token> m_Tokens;

        CharPosition m_CurrentCharPosition;
        char m_CurrentChar = '\0';
    };
}
