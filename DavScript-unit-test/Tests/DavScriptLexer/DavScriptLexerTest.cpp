#include "DavScriptLexerTest.h"

namespace davincpp::davscript
{
    DavScriptLexerTest::DavScriptLexerTest()
        : UnitTest("Testing the functionality of the DavScript lexer")
    { }


    void DavScriptLexerTest::onSetup()
    {
        DavScript davScript("../Tests/DavScriptLexer/test.dav");
        m_Lexer = std::make_unique<DavScriptLexer>(davScript);
    }

    void DavScriptLexerTest::execute()
    {
        m_Lexer->generateTokens();

        assertTrue(m_Lexer->getTokens().empty() == false);
    }
}
