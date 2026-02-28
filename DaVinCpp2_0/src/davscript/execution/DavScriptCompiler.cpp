#include "DavScriptCompiler.h"
#include <Console.h>
#include <ranges>
#include <error/DavScriptErrorFormatter.h>
#include <execution/ByteCastHelper.h>
#include <execution/DavScriptVirtualMachine.h>

namespace davincpp::davscript
{
    DavScriptCompiler::DavScriptCompiler(std::shared_ptr<Ast> ast)
        : m_Ast(std::move(ast))
    { }

    void DavScriptCompiler::reset()
    {
        m_VariableScopes.clear();
        m_CurrentScopeDepth = 0;
    }

    void DavScriptCompiler::loadStdLibraries(const std::vector<std::string>& usedNamespaces)
    {
        for (std::string_view namespaceName : usedNamespaces) {
            if (DAVSCRIPT_LIBRARIES.contains(namespaceName.data())) {
                const auto& registeredSymbols = DAVSCRIPT_LIBRARIES.at(namespaceName.data()).registeredSymbols;

                for (const auto& [symbolName, symbol] : registeredSymbols) {
                    if (symbol.symbolType == SymbolType::FUNCTION) {
                        m_RegisteredLibraryFunctions.emplace(
                            static_cast<uint32_t>(m_RegisteredLibraryFunctions.size()),
                            std::pair{Console::fmtTxt(namespaceName, symbolName), symbol.symbolFunction}
                        );
                    }
                }
            }
        }
    }

    void DavScriptCompiler::compile()
    {
        m_ByteCode = m_Ast->generateByteCode(this);
        checkForCompilationErrors();
    }

    void DavScriptCompiler::prepareVM(DavScriptVirtualMachine& vm) const
    {
        vm.loadByteCode(m_ByteCode);

        for (const auto& registeredLibraryFunction : m_RegisteredLibraryFunctions) {
            vm.registerLibraryFunction(registeredLibraryFunction.first, registeredLibraryFunction.second.second);
        }
    }

    uint32_t DavScriptCompiler::registerVariableScope(std::string_view variableName)
    {
        m_VariableScopes.emplace_back(variableName.data(), m_CurrentScopeDepth);
        return static_cast<uint32_t>(m_VariableScopes.size() - 1);
    }

    bool DavScriptCompiler::canAccessVariable(std::string_view variableName) const
    {
        for (int i = static_cast<int>(m_VariableScopes.size()) - 1; i >= 0; i--) {
            if (m_VariableScopes.at(i).variableName == variableName) {
                return true;
            }
        }

        return false;
    }

    std::vector<uint8_t> DavScriptCompiler::determineFunctionPtr(const Token& functionName)
    {
        int functionPtr = -1;
        for (const auto& registeredLibraryFunction : m_RegisteredLibraryFunctions) {
            if (registeredLibraryFunction.second.first == functionName.getActualValue()) {
                if (functionPtr != -1) {
                    logFoundAmbiguousFunctionError(functionName);
                    return {};
                }

                functionPtr = static_cast<int>(registeredLibraryFunction.first);
            }
        }

        // todo: determine custom function ptr

        return ByteCastHelper::nativeToBytes(static_cast<uint32_t>(functionPtr));
    }

    void DavScriptCompiler::logInvalidValueTypeError(const Token& typeToken, ValueType expectedType)
    {
        m_CompilerErrorMessages.push_back(DavScriptErrorFormatter::generateCompilerErrorInvalidValueType(typeToken, expectedType));
    }

    void DavScriptCompiler::logFoundAmbiguousFunctionError(const Token& functionName)
    {
        m_CompilerErrorMessages.push_back(DavScriptErrorFormatter::generateCompilerErrorFoundAmbiguousFunction(functionName));
    }

    void DavScriptCompiler::enterScope()
    {
        m_CurrentScopeDepth++;
    }

    void DavScriptCompiler::exitScope()
    {
        m_CurrentScopeDepth--;

        for (int i = 0; i < m_VariableScopes.size(); i++) {
            if (m_VariableScopes.at(i).scopeDepth > m_CurrentScopeDepth) {
                m_VariableScopes.erase(m_VariableScopes.begin() + i);
            }
        }
    }

    void DavScriptCompiler::checkForCompilationErrors() const
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
}
