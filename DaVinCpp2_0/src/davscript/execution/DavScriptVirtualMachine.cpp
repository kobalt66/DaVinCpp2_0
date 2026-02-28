#include "DavScriptVirtualMachine.h"

#include <Console.h>
#include <error/DavScriptErrorFormatter.h>
#include <error/DavScriptException.h>
#include <execution/ByteCastHelper.h>

#include <utility>

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
        if (m_Stack.empty()) {
            throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidStackAccessEmptyStack());
        }

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

    void DavScriptVirtualMachine::writeMemory(uint32_t ptr, const Value& value)
    {
        if (ptr >= m_Memory.size()) {
            throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidMemoryWriteAccess(ptr));
        }

        m_Memory.at(ptr) = value;
    }

    void DavScriptVirtualMachine::allocateMemory(uint8_t variablePtr)
    {
        if (variablePtr < m_Memory.size()) {
            return;
        }

        m_Memory.resize(variablePtr + 1);
    }

    void DavScriptVirtualMachine::loadByteCode(const std::vector<uint8_t>& byteCode)
    {
        m_CallStack = byteCode;
    }

    void DavScriptVirtualMachine::registerLibraryFunction(uint32_t functionPtr, std::function<void(DavScriptVirtualMachine*)> function)
    {
        m_RegisteredLibraryFunctions.emplace(functionPtr, function);
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
            case MOV_INT:
                processMovIntValueOperation();
                break;
            case MOV_BOOL:
                processMovBoolValueOperation();
                break;
            case MOV_FLOAT:
                processMovFloatValueOperation();
                break;
            case MOV_STRING:
                processMovStringValueOperation();
                break;
            case CALL:
                processFunctionCallOperation();
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

    void DavScriptVirtualMachine::processFunctionCallOperation()
    {
        uint32_t functionPtr = getPtrFromCallStack();

        if (!m_RegisteredLibraryFunctions.contains(functionPtr)) {
            throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidPointerAccess(functionPtr, PTR_CONTEXT_FUNCTION));
        }

        m_RegisteredLibraryFunctions.at(functionPtr)(this);
    }

    void DavScriptVirtualMachine::processStoreIntValueOperation()
    {
        uint8_t variablePtr = getPtrFromCallStack();
        int64_t value = getIntValueFromCallStack();

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::INT, value});
    }

    void DavScriptVirtualMachine::processStoreBoolValueOperation()
    {
        uint8_t variablePtr = getPtrFromCallStack();
        bool value = getBoolValueFromCallStack();

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::BOOL, value});
    }

    void DavScriptVirtualMachine::processStoreFloatValueOperation()
    {
        uint8_t variablePtr = getPtrFromCallStack();
        double value = getFloatValueFromCallStack();

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::DOUBLE, value});
    }

    void DavScriptVirtualMachine::processStoreStringValueOperation()
    {
        uint8_t variablePtr = getPtrFromCallStack();
        std::string value = getStringValueFromCallStack();

        allocateMemory(variablePtr);
        writeMemory(variablePtr, {ValueType::STRING, value});
    }

    void DavScriptVirtualMachine::processMovIntValueOperation()
    {
        int64_t value = getIntValueFromCallStack();
        m_Stack.emplace(ValueType::INT, value);
    }

    void DavScriptVirtualMachine::processMovBoolValueOperation()
    {
        bool value = getBoolValueFromCallStack();
        m_Stack.emplace(ValueType::BOOL, value);
    }

    void DavScriptVirtualMachine::processMovFloatValueOperation()
    {
        double value = getFloatValueFromCallStack();
        m_Stack.emplace(ValueType::DOUBLE, value);
    }

    void DavScriptVirtualMachine::processMovStringValueOperation()
    {
        std::string value = getStringValueFromCallStack();
        m_Stack.emplace(ValueType::STRING, value);
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

    uint32_t DavScriptVirtualMachine::getPtrFromCallStack()
    {
        advanceOperationPtr();
        uint32_t variablePtr = ByteCastHelper::bytesToInt(m_OperationPtr);
        advanceOperationPtrByN(sizeof(uint32_t));
        return variablePtr;
    }

    int64_t DavScriptVirtualMachine::getIntValueFromCallStack()
    {
        advanceOperationPtr();
        int64_t integer = ByteCastHelper::bytesToInt(m_OperationPtr);
        advanceOperationPtrByN(sizeof(int64_t));
        return integer;
    }

    bool DavScriptVirtualMachine::getBoolValueFromCallStack()
    {
        advanceOperationPtr();
        bool boolean = ByteCastHelper::bytesToBool(m_OperationPtr);
        advanceOperationPtrByN(sizeof(bool));
        return boolean;
    }

    double DavScriptVirtualMachine::getFloatValueFromCallStack()
    {
        advanceOperationPtr();
        double floatValue = ByteCastHelper::bytesToFloat(m_OperationPtr);
        advanceOperationPtrByN(sizeof(double));
        return floatValue;
    }

    std::string DavScriptVirtualMachine::getStringValueFromCallStack()
    {
        advanceOperationPtr();
        std::string stringValue = ByteCastHelper::bytesToString(m_OperationPtr);
        advanceOperationPtrByN(stringValue.size() + 1);
        return stringValue;
    }

    void DavScriptVirtualMachine::logRuntimeErrorInvalidOperation(uint8_t operation)
    {
        m_RuntimeErrorMessages.push_back(DavScriptErrorFormatter::generateRuntimeErrorInvalidOperation(operation));
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
