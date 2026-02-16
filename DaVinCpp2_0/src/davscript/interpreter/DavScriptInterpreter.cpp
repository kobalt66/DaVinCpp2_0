#include "DavScriptInterpreter.h"

#include <Console.h>
#include <filesystem>
#include <utility>
#include <error/DavScriptErrorFormatter.h>
#include <interpreter/ByteOperations.h>

namespace davincpp::davscript
{
    DavScriptInterpreter::DavScriptInterpreter(std::shared_ptr<Ast> ast)
        : m_Ast(std::move(ast)), m_ExitCode(NUL)
    { }

    void DavScriptInterpreter::run()
    {
        compile();
        execute();
    }

    uint8_t DavScriptInterpreter::registerRuntimeConstant(StackValue value)
    {
        for (auto& [key, v]: m_RuntimeConstants) {
            if (v == value) {
                return key;
            }
        }

        auto ptr = static_cast<uint8_t>(m_RuntimeConstants.size());
        m_RuntimeConstants.emplace(ptr, value);
        return ptr;
    }

    void DavScriptInterpreter::logCompilerErrorInvalidValueType(const Token& typeToken, StackValueType expectedType)
    {
        m_CompilerErrorMessages.push_back(DavScriptErrorFormatter::generateCompilerErrorInvalidValueType(typeToken, expectedType));
    }

    const std::stack<StackValue>& DavScriptInterpreter::getStack() const
    {
        return m_Stack;
    }

    void DavScriptInterpreter::compile()
    {
        m_CallStack = m_Ast->generateByteCode(this);
        checkForCompilationErrors();
    }

    void DavScriptInterpreter::execute()
    {
        uint8_t* callStack = m_CallStack.data();

        bool run = true;
        while (run) {
            uint8_t operation = *callStack++;
            switch (operation) {
                case ST_INT:
                    processStoreIntOperation(callStack);
                    break;
                case END:
                    m_ExitCode = *callStack++;
                    run = false;
                    break;
                case NUL: break;
                default: throw std::runtime_error(DavScriptErrorFormatter::generateRuntimeErrorInvalidOperation(operation));
            }
        }

        if (m_ExitCode != NUL) {
            throw std::runtime_error(DavScriptErrorFormatter::generateRuntimeErrorFailureCode(m_ExitCode));
        }
    }

    void DavScriptInterpreter::checkForCompilationErrors() const
    {
        if (m_CompilerErrorMessages.empty()) {
            return;
        }

        std::stringstream errorOutput;
        errorOutput << std::endl;

        for (std::string_view errorMessage : m_CompilerErrorMessages) {
            errorOutput << errorMessage.data() << std::endl;
        }

        errorOutput << std::endl;

        throw std::runtime_error(Console::fmtErr(
            "DavScript failed during compilation!",
            errorOutput.str(),
            m_CompilerErrorMessages.size(), " error(s) occurred during the compilation phase.")
        );
    }

    void DavScriptInterpreter::processStoreIntOperation(uint8_t* operationPtr)
    {
        uint8_t runtimeConstantPtr = *operationPtr++;
        StackValue value = m_RuntimeConstants.at(runtimeConstantPtr);
        m_Stack.push(value);
    }
}
