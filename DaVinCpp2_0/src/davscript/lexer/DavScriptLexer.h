#pragma once
#include <DavScript.h>

namespace davincpp::davscript
{
    class DavScriptLexer
    {
    public:
        explicit DavScriptLexer(DavScript davScript);

    private:
        DavScript m_DavScript;
    };
}
