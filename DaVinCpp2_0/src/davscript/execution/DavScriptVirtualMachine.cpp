#include "DavScriptVirtualMachine.h"

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
        uint8_t* operationPtr = m_CallStack.data();

        bool run = true;
        while (run) {
            switch (uint8_t operation = *operationPtr++) {
                case ST_INT:
                case ST_BOOL:
                case ST_DOUBLE:
                case ST_STRING:
                    processStoreNativeValueOperation(operationPtr);
                    break;
                case END:
                    m_ExitCode = *operationPtr++;
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

    StackValue DavScriptVirtualMachine::popStackValue()
    {
        const StackValue value = m_Stack.top();
        m_Stack.pop();
        return value;
    }

    StackValue DavScriptVirtualMachine::readMemory(uint32_t ptr) const
    {
        if (ptr >= m_Memory.size()) {
            throw std::runtime_error(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryAccess(ptr));
        }

        return m_Memory.at(ptr);
    }

    void DavScriptVirtualMachine::writeMemory(uint32_t ptr, StackValue value)
    {
        if (ptr >= m_Memory.size()) {
            throw std::runtime_error(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryAccess(ptr));
        }

        m_Memory.at(ptr) = value;
    }

    void DavScriptVirtualMachine::loadByteCode(const std::vector<uint8_t>& byteCode)
    {
        m_CallStack = std::move(byteCode);
    }

    void DavScriptVirtualMachine::registerRuntimeConstantsPool(std::vector<StackValue> runtimeConstantsPool)
    {
        m_RuntimeConstantsPool = std::move(runtimeConstantsPool);
    }

    void DavScriptVirtualMachine::processStoreNativeValueOperation(uint8_t* operationPtr)
    {
        uint8_t variablePtr = *operationPtr++;
        uint32_t valuePtr = getVariablePtrFromCallStack(operationPtr);

        allocateMemory();
        writeMemory(variablePtr, m_RuntimeConstantsPool.at(valuePtr));
    }

    void DavScriptVirtualMachine::allocateMemory()
    {
        m_Memory.resize(m_Memory.size() + 1);
    }

    uint32_t DavScriptVirtualMachine::getVariablePtrFromCallStack(uint8_t* operationPtr)
    {
        std::array<uint8_t, 4> ptrBytes{};
        std::ranges::copy(operationPtr, operationPtr + 4, ptrBytes.begin());
        return ByteCastHelper::join32Bit(ptrBytes);
    }
}
