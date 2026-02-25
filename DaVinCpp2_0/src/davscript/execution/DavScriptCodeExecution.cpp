#include "DavScriptCodeExecution.h"
#include <error/DavScriptErrorFormatter.h>

namespace davincpp::davscript
{
    DavScriptCodeExecution::DavScriptCodeExecution(std::shared_ptr<Ast> ast)
        : m_Compiler(std::move(ast))
    { }

    void DavScriptCodeExecution::run()
    {
        m_Compiler.reset();

        std::vector<uint8_t> byteCode = m_Compiler.compile();
        m_VM.loadByteCode(byteCode);
        m_VM.execute();
    }

    const DavScriptCompiler& DavScriptCodeExecution::getCompiler() const
    {
        return m_Compiler;
    }

    const DavScriptVirtualMachine& DavScriptCodeExecution::getVM() const
    {
        return m_VM;
    }
}
