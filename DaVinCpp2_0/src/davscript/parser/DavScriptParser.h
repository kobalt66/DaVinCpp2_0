#pragma once
#include <vector>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptParser
    {
    public:
        explicit DavScriptParser(std::vector<Token>& tokens);

        void generateAst();

    private:
        std::vector<Token> m_Tokens;
    };
}
