#pragma once
#include <memory>
#include <stack>
#include <execution/ByteOperations.h>
#include <execution/dto/Value.h>

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

        [[nodiscard]] Value popStackValue();

        [[nodiscard]] Value readMemory(uint32_t ptr) const;
        void writeMemory(uint32_t ptr, Value value);

        void loadByteCode(const std::vector<uint8_t>& byteCode);

    private:
        bool interpretOperation();

        void processStoreIntValueOperation();
        void processStoreBoolValueOperation();
        void processStoreFloatValueOperation();
        void processStoreStringValueOperation();

        uint8_t advanceOperationPtr();
        void advanceOperationPtrByN(size_t n);

        void allocateMemory(uint8_t variablePtr);
        [[nodiscard]] uint32_t getVariablePtrFromCallStack();

        void logRuntimeErrorInvalidOperation(uint8_t operation);
        void checkForCompilationErrors() const;

    private:
        uint8_t* m_OperationPtr = nullptr;
        std::vector<uint8_t> m_CallStack;

        std::stack<Value> m_Stack;
        std::vector<Value> m_Memory;

        uint8_t m_ExitCode = NUL;

        std::vector<std::string> m_RuntimeErrorMessages;
    };
}
