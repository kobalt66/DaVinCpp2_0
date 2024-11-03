#include "DavScriptLexerTest.h"
#include <algorithm>

namespace davincpp::davscript
{
    DavScriptLexerTest::DavScriptLexerTest()
        : UnitTest("Testing the functionality of the DavScript lexer")
    { }


    void DavScriptLexerTest::execute()
    {
        assertTestStep(testSingleCharTokens());
        assertTestStep(testComments());
        assertTestStep(testVariableType());
        assertTestStep(testWrongVariableType());
        assertTestStep(testWords());
        assertTestStep(testNumbers());
    }


    void DavScriptLexerTest::testSingleCharTokens()
    {
        DavScript davScript("../Tests/DavScriptLexer/TestFiles/singleCharTokens.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(SINGLE_CHAR_TOKENS.size(), getTokenCountByTokenRoles({NORMAL, OPERATOR}, tokens));

        for (Token& token : tokens) {
            assertEquals(1, token.getActualValue().size());
            assertTrue(SINGLE_CHAR_TOKENS.find(token.getActualValue().at(0)) != SINGLE_CHAR_TOKENS.end());
        }
    }

    void DavScriptLexerTest::testComments()
    {
        DavScript davScript("../Tests/DavScriptLexer/TestFiles/comments.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(3, getTokenCountByTokenRole(COMMENT, tokens));
        assertEquals("# this is a comment #", tokens.at(0).getActualValue());
    }

    void DavScriptLexerTest::testVariableType()
    {
        DavScript davScript("../Tests/DavScriptLexer/TestFiles/variableTypes.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(VARIABLE_TYPE_TOKENS.size(), getTokenCountByTokenRole(VARIABLETYPE, tokens));

        for (Token& token : tokens) {
            assertTrue(findTokenInWhiteListExept(VARIABLE_TYPE_TOKENS, {NEWLINE}, token));
        }
    }

    void DavScriptLexerTest::testWrongVariableType()
    {
        DavScript davScript("../Tests/DavScriptLexer/TestFiles/wrongVariableTypes.dav");
        DavScriptLexer lexer(davScript);
        assertGetException(lexer.generateTokens(), "TODO: CHANGE ERROR MESSAGE TO SPECIAL DAVSCRIPT ERROR OUTPUT! Undefined variable type was used.");
    }

    void DavScriptLexerTest::testWords()
    {
        DavScript davScript("../Tests/DavScriptLexer/TestFiles/words.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(2, getTokenCountByTokenRole(IDENTIFIER, tokens));
        assertEquals(2, getTokenCountByTokenRole(KEYWORD, tokens));
        assertEquals(2, getTokenCountByTokenRole(VALUETYPE, tokens));
        assertEquals(2, getTokenCountByTokenRole(DATAVALUE, tokens));
    }

    void DavScriptLexerTest::testNumbers()
    {
        DavScript davScript("../Tests/DavScriptLexer/TestFiles/numbers.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(10, getTokenCountByTokenRole(DATAVALUE, tokens));
    }


    int DavScriptLexerTest::getTokenCountByTokenRole(TokenRole role, const std::vector<Token>& tokens)
    {
        int totalTokenCount = 0;

        for (const Token& token : tokens) {
            totalTokenCount += static_cast<int>(token.getTokenRole() == role);
        }

        return totalTokenCount;
    }

    int DavScriptLexerTest::getTokenCountByTokenRoles(std::vector<TokenRole>&& roles, const std::vector<Token>& tokens)
    {
        int totalTokenCount = 0;

        for (const Token& token : tokens) {
            totalTokenCount += static_cast<int>(
                std::find(roles.begin(), roles.end(), token.getTokenRole()) != roles.end()
                    );
        }

        return totalTokenCount;
    }

    bool DavScriptLexerTest::findTokenInWhiteListExept(const std::unordered_map<std::string, TokenType>& whiteList, std::vector<TokenType>&& exept, const Token& token)
    {
        return
            whiteList.find(token.getActualValue()) != whiteList.end() ||
            std::find(exept.begin(), exept.end(), token.getTokenType()) != exept.end();
    }
}
