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

    private:
        char advanceChar();

    private:
        DavScript m_DavScript;

        std::vector<Token> m_Tokens;

        TokenPosition m_CurrentCharPosition;
        char m_CurrentChar = '\0';
    };
}
