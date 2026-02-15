#include "DavScriptInterpreter.h"

namespace davincpp::davscript
{
    DavScriptInterpreter::DavScriptInterpreter(std::shared_ptr<Ast> ast)
        : m_Ast(std::move(ast))
    { }

    void DavScriptInterpreter::run()
    {

    }

    void DavScriptInterpreter::compile()
    {
        std::vector<char> byteCode = m_Ast->generateByteCode();
    }

    void DavScriptInterpreter::execute()
    {

    }
}
