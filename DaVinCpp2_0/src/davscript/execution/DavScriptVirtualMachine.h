#pragma once
#include <filesystem>
#include <functional>
#include <memory>
#include <stack>
#include <execution/ByteOperations.h>
#include <execution/dto/Value.h>

namespace davincpp::davscript
{
static constexpr uint8_t ZERO          = NUL;
static constexpr uint8_t ERROR         = 1;
static constexpr uint8_t FATAL_ERROR   = 2;
static constexpr uint8_t CMD_NOT_FOUND = 127;

static auto PTR_CONTEXT_FUNCTION = "function";

class DavScriptVirtualMachine final
{
public:
    explicit DavScriptVirtualMachine(std::filesystem::path projectDirectory);

    void reset();
    void prepareVM();
    void execute();

    [[nodiscard]] Value popStackValue();
    [[nodiscard]] Value tryPopStackValue();

    [[nodiscard]] Value readMemory(uint32_t ptr) const;
    void                writeMemory(uint32_t ptr, const Value& value);
    void                allocateMemory(uint8_t variablePtr);

private:
    bool interpretOperation();

    void processLoadLibraryOperation();

    void processFunctionCallOperation();

    void processStoreIntValueOperation();
    void processStoreBoolValueOperation();
    void processStoreFloatValueOperation();
    void processStoreStringValueOperation();

    void processMovIntValueOperation();
    void processMovBoolValueOperation();
    void processMovFloatValueOperation();
    void processMovStringValueOperation();

    void useNamespace(std::string_view namespaceName);

    uint8_t advanceOperationPtr();
    void    advanceOperationPtrByN(size_t n);

    [[nodiscard]] uint32_t    getPtrFromCallStack();
    [[nodiscard]] int64_t     getIntValueFromCallStack();
    [[nodiscard]] bool        getBoolValueFromCallStack();
    [[nodiscard]] double      getFloatValueFromCallStack();
    [[nodiscard]] std::string getStringValueFromCallStack();

    void logRuntimeErrorInvalidOperation(uint8_t operation);
    void checkForCompilationErrors() const;

private:
    std::filesystem::path m_ProjectDirectory;

    uint8_t*             m_OperationPtr = nullptr;
    std::vector<uint8_t> m_CallStack;

    std::unordered_map<uint32_t, std::function<void(DavScriptVirtualMachine*)>>
                             m_RegisteredLibraryFunctions;
    std::vector<std::string> m_UsedNamespaces;

    std::stack<Value>  m_Stack;
    std::vector<Value> m_Memory;

    uint8_t m_ExitCode = NUL;

    std::vector<std::string> m_RuntimeErrorMessages;
};
}  // namespace davincpp::davscript
