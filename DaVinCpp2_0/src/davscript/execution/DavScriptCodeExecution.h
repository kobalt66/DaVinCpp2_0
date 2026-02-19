#pragma once
#include <memory>
#include <ast/Ast.h>
#include <execution/DavScriptCompiler.h>
#include <execution/DavScriptVirtualMachine.h>

namespace davincpp::davscript
{
    class DavScriptCodeExecution final
    {
    public:
        explicit DavScriptCodeExecution(std::shared_ptr<Ast> ast);

        void run();

        [[nodiscard]] const DavScriptCompiler& getCompiler() const;
        [[nodiscard]] const DavScriptVirtualMachine& getVM() const;

    private:
        DavScriptCompiler m_Compiler;
        DavScriptVirtualMachine m_VM;
    };
}
