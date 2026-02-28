#pragma once
#include <functional>
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

    static auto PTR_CONTEXT_FUNCTION = "function";

    class DavScriptVirtualMachine final
    {
    public:
        void reset();
        void execute();

        [[nodiscard]] Value popStackValue();

        [[nodiscard]] Value readMemory(uint32_t ptr) const;
        void writeMemory(uint32_t ptr, const Value& value);
        void allocateMemory(uint8_t variablePtr);

        void loadByteCode(const std::vector<uint8_t>& byteCode);
        void registerLibraryFunction(uint32_t functionPtr, std::function<void(DavScriptVirtualMachine*)> function);

    private:
        bool interpretOperation();

        void processFunctionCallOperation();

        void processStoreIntValueOperation();
        void processStoreBoolValueOperation();
        void processStoreFloatValueOperation();
        void processStoreStringValueOperation();

        void processMovIntValueOperation();
        void processMovBoolValueOperation();
        void processMovFloatValueOperation();
        void processMovStringValueOperation();

        uint8_t advanceOperationPtr();
        void advanceOperationPtrByN(size_t n);

        [[nodiscard]] uint32_t getPtrFromCallStack();
        [[nodiscard]] int64_t getIntValueFromCallStack();
        [[nodiscard]] bool getBoolValueFromCallStack();
        [[nodiscard]] double getFloatValueFromCallStack();
        [[nodiscard]] std::string getStringValueFromCallStack();

        void logRuntimeErrorInvalidOperation(uint8_t operation);
        void checkForCompilationErrors() const;

    private:
        uint8_t* m_OperationPtr = nullptr;
        std::vector<uint8_t> m_CallStack;

        std::unordered_map<uint32_t, std::function<void(DavScriptVirtualMachine*)>> m_RegisteredLibraryFunctions;

        std::stack<Value> m_Stack;
        std::vector<Value> m_Memory;

        uint8_t m_ExitCode = NUL;

        std::vector<std::string> m_RuntimeErrorMessages;
    };
}
