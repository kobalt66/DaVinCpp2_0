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
    };
}
