#include "DavScriptVirtualMachine.h"

#include <Console.h>
#include <error/DavScriptErrorFormatter.h>
#include <execution/ByteCastHelper.h>

namespace davincpp::davscript
{
    void DavScriptVirtualMachine::reset()
    {
        m_CallStack.clear();
        while (!m_Stack.empty()) m_Stack.pop();
        m_Memory.clear();
    }

    void DavScriptVirtualMachine::execute()
    {
        try {
            while (interpretOperation()) { }
        } catch (std::runtime_error& e) {
            m_RuntimeErrorMessages.emplace_back(e.what());
            m_ExitCode = ERROR;
        } catch (const std::exception& e) {
            m_RuntimeErrorMessages.emplace_back(DavScriptErrorFormatter::generateRuntimeUnexpectedError(e.what()));
            m_ExitCode = FATAL_ERROR;
        }

        if (m_ExitCode != ZERO) {
            m_RuntimeErrorMessages.emplace_back(DavScriptErrorFormatter::generateRuntimeExitCode(m_ExitCode));
            checkForCompilationErrors();
        }
    }

    StackValue DavScriptVirtualMachine::popStackValue()
    {
        const StackValue value = m_Stack.top();
        m_Stack.pop();
        return value;
    }

    StackValue DavScriptVirtualMachine::readMemory(uint32_t ptr) const
    {
        if (ptr >= m_Memory.size()) {
            throw std::runtime_error(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryReadAccess(ptr));
        }

        return m_Memory.at(ptr);
    }

    void DavScriptVirtualMachine::writeMemory(uint32_t ptr, StackValue value)
    {
        if (ptr >= m_Memory.size()) {
            throw std::runtime_error(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryWriteAccess(ptr));
        }

        m_Memory.at(ptr) = value;
    }

    void DavScriptVirtualMachine::loadByteCode(const std::vector<uint8_t>& byteCode)
    {
        m_CallStack = byteCode;
    }

    void DavScriptVirtualMachine::registerRuntimeConstantsPool(std::vector<StackValue> runtimeConstantsPool)
    {
        m_RuntimeConstantsPool = std::move(runtimeConstantsPool);
    }

    bool DavScriptVirtualMachine::interpretOperation()
    {
        switch (const uint8_t operation = advanceOperationPtr()) {
            case ST_INT:
            case ST_BOOL:
            case ST_DOUBLE:
            case ST_STRING:
                processStoreNativeValueOperation();
                break;
            case END:
                m_ExitCode = advanceOperationPtr();
                return false;
            case DIE:
                m_ExitCode = ERROR;
                return false;
            case NUL: break;
            default:
                logRuntimeErrorInvalidOperation(operation);
                m_ExitCode = CMD_NOT_FOUND;
                return false;
        }

        return true;
    }

    void DavScriptVirtualMachine::processStoreNativeValueOperation()
    {
        uint8_t variablePtr = advanceOperationPtr();
        uint32_t valuePtr = getVariablePtrFromCallStack();

        allocateMemory();
        writeMemory(variablePtr, m_RuntimeConstantsPool.at(valuePtr));
    }

    uint8_t DavScriptVirtualMachine::advanceOperationPtr()
    {
        if (m_OperationPtr + 1 >= m_CallStack.size()) {
            return DIE;
        }

        m_OperationPtr++;
        return m_CallStack.at(m_OperationPtr);
    }

    void DavScriptVirtualMachine::allocateMemory()
    {
        m_Memory.resize(m_Memory.size() + 1);
    }

    uint32_t DavScriptVirtualMachine::getVariablePtrFromCallStack()
    {
        return ByteCastHelper::join32Bit({
            advanceOperationPtr(),
            advanceOperationPtr(),
            advanceOperationPtr(),
            advanceOperationPtr(),
        });
    }

    void DavScriptVirtualMachine::logRuntimeErrorInvalidOperation(uint8_t operation)
    {
        m_RuntimeErrorMessages.emplace_back(DavScriptErrorFormatter::generateRuntimeErrorInvalidOperation(operation));
    }

    void DavScriptVirtualMachine::checkForCompilationErrors() const
    {
        if (m_RuntimeErrorMessages.empty()) {
            return;
        }

        std::stringstream errorOutput;
        errorOutput << std::endl;

        for (std::string_view errorMessage : m_RuntimeErrorMessages) {
            errorOutput << errorMessage.data() << std::endl;
        }

        errorOutput << std::endl;

        throw std::runtime_error(errorOutput.str());
    }
}
