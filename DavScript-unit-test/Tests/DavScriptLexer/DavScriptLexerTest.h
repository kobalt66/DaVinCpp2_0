#pragma once
#include <UnitTest.h>
#include <lexer/DavScriptLexer.h>

namespace davincpp::davscript
{
    class DavScriptLexerTest : public unittest::UnitTest
    {
    public:
        explicit DavScriptLexerTest();

        void onSetup() override;
        void execute() override;

    private:
        std::unique_ptr<DavScriptLexer> m_Lexer = nullptr;
    };
}
