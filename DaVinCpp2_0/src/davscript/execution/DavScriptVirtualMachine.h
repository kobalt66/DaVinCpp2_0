#pragma once
#include <memory>
#include <stack>
#include <execution/ByteOperations.h>
#include <execution/dto/StackValue.h>

namespace davincpp::davscript
{
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
        void processStoreNativeValueOperation(uint8_t* operationPtr);

        void allocateMemory();
        static uint32_t getVariablePtrFromCallStack(uint8_t* operationPtr);

    private:
        std::vector<StackValue> m_RuntimeConstantsPool;

        std::vector<uint8_t> m_CallStack;
        std::stack<StackValue> m_Stack;
        std::vector<StackValue> m_Memory;

        uint8_t m_ExitCode = NUL;
    };
}
