#pragma once
#include <UnitTest.h>
#include <lexer/DavScriptLexer.h>

namespace davincpp::davscript
{
    class DavScriptLexerTest : public unittest::UnitTest
    {
    public:
        explicit DavScriptLexerTest();

        void execute() override;

    private:
        static void testSingleCharTokens();
        static void testComments();
        static void testVariableType();
        static void testWrongVariableType();
        static void testWords();
        static void testNumbers();

        static int getTokenCountByTokenRole(TokenRole role, const std::vector<Token>& tokens);
        static int getTokenCountByTokenRoles(std::vector<TokenRole>&& roles, const std::vector<Token>& tokens);
        static bool findTokenInWhiteListExept(const std::unordered_map<std::string, TokenType>& whiteList, std::vector<TokenType>&& exept, const Token& token);
    };
}
