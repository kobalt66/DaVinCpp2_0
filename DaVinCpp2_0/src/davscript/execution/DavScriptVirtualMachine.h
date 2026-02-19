#pragma once
#include <memory>
#include <stack>
#include <execution/ByteOperations.h>
#include <execution/dto/StackValue.h>

namespace davincpp::davscript
{
    static constexpr uint8_t ZERO = NUL;
    static constexpr uint8_t ERROR = 1;
    static constexpr uint8_t FATAL_ERROR = 2;
    static constexpr uint8_t CMD_NOT_FOUND = 127;

    class DavScriptVirtualMachine final
    {
    public:
        void reset();
        void execute();

        [[nodiscard]] StackValue popStackValue();

        [[nodiscard]] StackValue readMemory(uint32_t ptr) const;
        void writeMemory(uint32_t ptr, StackValue value);

        void loadByteCode(const std::vector<uint8_t>& byteCode);
        void registerRuntimeConstantsPool(std::vector<StackValue> runtimeConstantsPool);

    private:
        bool interpretOperation();

        void processStoreNativeValueOperation();

        uint8_t advanceOperationPtr();

        void allocateMemory(uint8_t variablePtr);
        [[nodiscard]] uint32_t getVariablePtrFromCallStack();

        void logRuntimeErrorInvalidOperation(uint8_t operation);
        void checkForCompilationErrors() const;

    private:
        std::vector<StackValue> m_RuntimeConstantsPool;

        size_t m_OperationPtr = -1;
        std::vector<uint8_t> m_CallStack;

        std::stack<StackValue> m_Stack;
        std::vector<StackValue> m_Memory;

        uint8_t m_ExitCode = NUL;

        std::vector<std::string> m_RuntimeErrorMessages;
    };
}
