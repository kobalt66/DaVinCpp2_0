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
        void lexSingleCharTokens();
        void lexMultiCharTokens();
        void lexComment();
        void lexVariableType();
        void lexWordToken();

        char advanceChar();
        char peakNextChar();
        [[nodiscard]] CharPosition getNextcharPosition() const;

        [[nodiscard]] bool isSingleCharToken() const;
        [[nodiscard]] bool isOperatorToken() const;

        static bool charOnBlackList(char character, const std::vector<char>& blackList);
        static bool tokenValueOnWhiteList(std::string_view tokenValue, const std::unordered_map<std::string, TokenType>& whiteList);
        static bool charOnInCharList(char character, const std::string& charList);

    private:
        DavScript m_DavScript;

        std::vector<Token> m_Tokens;

        CharPosition m_CurrentCharPosition;
        char m_CurrentChar = '\0';
    };

#define tryAdvanceChar() \
    if (peakNextChar() == T_EOF) { \
        return; \
    } \
    advanceChar();
}
