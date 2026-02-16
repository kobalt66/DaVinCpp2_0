#pragma once
#include <DavScript.h>
#include <memory>
#include <stack>
#include <unordered_map>
#include <ast/Ast.h>
#include <interpreter/dto/StackValue.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptInterpreter final
    {
    public:
        explicit DavScriptInterpreter(std::shared_ptr<Ast> ast);

        void run();

        [[nodiscard]] uint8_t registerRuntimeConstant(StackValue value);

        void logCompilerErrorInvalidValueType(const Token& typeToken, StackValueType expectedType);

        [[nodiscard]] const std::stack<StackValue>& getStack() const;

    private:
        void compile();
        void execute();

        void checkForCompilationErrors() const;

        void processStoreIntOperation(uint8_t* operationPtr);

    private:
        std::shared_ptr<Ast> m_Ast;
        std::stack<StackValue> m_Stack;
        std::unordered_map<uint8_t, StackValue> m_RuntimeConstants;
        std::vector<uint8_t> m_CallStack;

        uint8_t m_ExitCode;

        std::vector<std::string> m_CompilerErrorMessages;
    };
}
