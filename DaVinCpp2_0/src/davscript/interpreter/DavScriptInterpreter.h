#pragma once
#include <memory>
#include <stack>
#include <ast/Ast.h>
#include <interpreter/dto/StackValue.h>

namespace davincpp::davscript
{
    class DavScriptInterpreter final
    {
    public:
        explicit DavScriptInterpreter(std::shared_ptr<Ast> ast);

        void run();

    private:
        void compile();
        void execute();

        void allocateValue(StackValue value);
        void getStackTop(StackValue& value);

    private:
        std::stack<StackValue> m_Stack;
        std::unique_ptr<char[]> m_CallStack;

        std::shared_ptr<Ast> m_Ast;
    };
}
