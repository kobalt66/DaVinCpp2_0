#include "DavScriptLexerTest.h"

namespace davincpp::davscript
{
    DavScriptLexerTest::DavScriptLexerTest()
        : UnitTest("Testing the functionality of the DavScript lexer")
    { }


    void DavScriptLexerTest::execute()
    {
        assertTestStep(testSingleCharTokens());
        assertTestStep(testComments());
    }


    void DavScriptLexerTest::testSingleCharTokens()
    {
        DavScript davScript("../Tests/DavScriptLexer/singleCharTokens.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(SINGLE_CHAR_TOKENS.size(), tokens.size());

        for (Token& token : tokens) {
            assertEquals(1, token.getActualValue().size());
            assertTrue(SINGLE_CHAR_TOKENS.find(token.getActualValue().at(0)) != SINGLE_CHAR_TOKENS.end());
        }
    }

    void DavScriptLexerTest::testComments()
    {
        DavScript davScript("../Tests/DavScriptLexer/comments.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        std::vector<Token> tokens = lexer.getTokens();

        assertEquals(5, tokens.size());
        assertEquals("# this is a comment #", tokens.at(0).getActualValue());
    }
}
