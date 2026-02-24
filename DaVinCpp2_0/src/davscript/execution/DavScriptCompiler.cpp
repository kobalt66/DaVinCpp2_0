#include "DavScriptCompiler.h"

#include <Console.h>
#include <error/DavScriptErrorFormatter.h>

namespace davincpp::davscript
{
    DavScriptCompiler::DavScriptCompiler(std::shared_ptr<Ast> ast)
        : m_Ast(std::move(ast))
    { }

    void DavScriptCompiler::reset()
    {
        m_VariableScopes.clear();
        m_CurrentScopeDepth = 0;
        m_RuntimeConstantsPool.clear();
    }

    std::vector<uint8_t> DavScriptCompiler::compile()
    {
        std::vector<uint8_t> callStack = m_Ast->generateByteCode(this);
        checkForCompilationErrors();
        return callStack;
    }

    uint8_t DavScriptCompiler::registerVariableScope(std::string_view variableName)
    {
        m_VariableScopes.emplace_back(variableName.data(), m_CurrentScopeDepth);
        return static_cast<uint8_t>(m_VariableScopes.size() - 1);
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

    uint32_t DavScriptCompiler::registerRuntimeConstant(Value value)
    {
        for (int i = 0; i < m_RuntimeConstantsPool.size(); i++) {
            if (m_RuntimeConstantsPool.at(i) == value) {
                return static_cast<uint32_t>(i);
            }
        }

        const auto ptr = static_cast<uint32_t>(m_RuntimeConstantsPool.size());
        m_RuntimeConstantsPool.push_back(value);
        return ptr;
    }

    const std::vector<Value>& DavScriptCompiler::getRuntimeConstantsPool() const
    {
        return m_RuntimeConstantsPool;
    }

    void DavScriptCompiler::logCompilerErrorInvalidValueType(const Token& typeToken, ValueType expectedType)
    {
        m_CompilerErrorMessages.push_back(DavScriptErrorFormatter::generateCompilerErrorInvalidValueType(typeToken, expectedType));
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
