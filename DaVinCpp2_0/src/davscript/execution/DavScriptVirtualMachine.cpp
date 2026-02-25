#include "DavScriptVirtualMachine.h"

#include <Console.h>
#include <error/DavScriptErrorFormatter.h>
#include <error/DavScriptException.h>
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
        } catch (const DavScriptException& e) {
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

    Value DavScriptVirtualMachine::popStackValue()
    {
        const Value value = m_Stack.top();
        m_Stack.pop();
        return value;
    }

    Value DavScriptVirtualMachine::readMemory(uint32_t ptr) const
    {
        if (ptr >= m_Memory.size()) {
            throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryReadAccess(ptr));
        }

        return m_Memory.at(ptr);
    }

    void DavScriptVirtualMachine::writeMemory(uint32_t ptr, Value value)
    {
        if (ptr >= m_Memory.size()) {
            throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryWriteAccess(ptr));
        }

        m_Memory.at(ptr) = value;
    }

    void DavScriptVirtualMachine::loadByteCode(const std::vector<uint8_t>& byteCode)
    {
        m_CallStack = byteCode;
    }

    bool DavScriptVirtualMachine::interpretOperation()
    {
        switch (const uint8_t operation = advanceOperationPtr()) {
            case ST_INT:
                processStoreIntValueOperation();
                break;
            case ST_BOOL:
                processStoreBoolValueOperation();
                break;
            case ST_FLOAT:
                processStoreFloatValueOperation();
                break;
            case ST_STRING:
                processStoreStringValueOperation();
                break;
            case END:
                m_ExitCode = advanceOperationPtr();
                return false;
            case DIE:
                m_ExitCode = ERROR;
                return false;
            case NUL:
                return true;
            default:
                logRuntimeErrorInvalidOperation(operation);
                m_ExitCode = CMD_NOT_FOUND;
                return false;
        }

        return true;
    }

    void DavScriptVirtualMachine::processStoreIntValueOperation()
    {
        uint8_t variablePtr = getVariablePtrFromCallStack();
        advanceOperationPtr();

        int64_t value = ByteCastHelper::bytesToInt(m_OperationPtr);
        advanceOperationPtrByN(sizeof(int64_t));

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::INT, value});
    }

    void DavScriptVirtualMachine::processStoreBoolValueOperation()
    {
        uint8_t variablePtr = getVariablePtrFromCallStack();
        advanceOperationPtr();

        bool value = ByteCastHelper::bytesToBool(m_OperationPtr);
        advanceOperationPtrByN(sizeof(bool));

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::BOOL, value});
    }

    void DavScriptVirtualMachine::processStoreFloatValueOperation()
    {
        uint8_t variablePtr = getVariablePtrFromCallStack();
        advanceOperationPtr();

        double value = ByteCastHelper::bytesToFloat(m_OperationPtr);
        advanceOperationPtrByN(sizeof(double));

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::DOUBLE, value});
    }

    void DavScriptVirtualMachine::processStoreStringValueOperation()
    {
        uint8_t variablePtr = getVariablePtrFromCallStack();
        advanceOperationPtr();

        std::string value = ByteCastHelper::bytesToString(m_OperationPtr);
        advanceOperationPtrByN(value.size() + 1);

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::STRING, value});
    }

    uint8_t DavScriptVirtualMachine::advanceOperationPtr()
    {
        if (m_OperationPtr == nullptr) {
            m_OperationPtr = m_CallStack.data();
            return *m_OperationPtr;
        }

        if (m_OperationPtr + 1 - m_CallStack.data() >= m_CallStack.size()) {
            return DIE;
        }

        m_OperationPtr++;
        return *m_OperationPtr;
    }

    void DavScriptVirtualMachine::advanceOperationPtrByN(size_t n)
    {
        m_OperationPtr += n - 1;
    }

    void DavScriptVirtualMachine::allocateMemory(uint8_t variablePtr)
    {
        if (variablePtr < m_Memory.size()) {
            return;
        }

        m_Memory.resize(variablePtr + 1);
    }

    uint32_t DavScriptVirtualMachine::getVariablePtrFromCallStack()
    {
        advanceOperationPtr();
        uint32_t variablePtr = ByteCastHelper::bytesToInt(m_OperationPtr);
        advanceOperationPtrByN(sizeof(uint32_t));
        return variablePtr;
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
