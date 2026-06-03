#include "DavScriptCompiler.h"

#include <Console.h>
#include <error/DavScriptErrorFormatter.h>
#include <execution/ByteCastHelper.h>
#include <execution/DavScriptVirtualMachine.h>
#include <ranges>
#include <utility>

namespace davincpp::davscript {
DavScriptCompiler::DavScriptCompiler(
    std::shared_ptr<Ast> ast, const std::vector<IdentifierNode>& usedNamespaces,
    std::filesystem::path projectDirectory)
    : m_Ast(std::move(ast)), m_ProjectDirectory(std::move(projectDirectory)) {
    for (const auto& usedNamespace : usedNamespaces) {
        useNamespace(usedNamespace.getName());
    }
}

void DavScriptCompiler::reset() {
    m_VariableScopes.clear();
    m_CurrentScopeDepth = 0;
}

void DavScriptCompiler::compile() {
    m_ByteCode = m_Ast->generateByteCode(this);
    checkForCompilationErrors();
}

void DavScriptCompiler::saveByteCode() {
    std::filesystem::path binDirectory = m_ProjectDirectory.append("bin");
    if (!DaVinCppFileSystem::cists(binDirectory)) {
        std::filesystem::create_directory(binDirectory);
    }

    std::string output(m_ByteCode.begin(), m_ByteCode.end());
    DaVinCppFileSystem::writeFile(
        binDirectory
            .append(m_Ast->getModuleNamespace().getName().getActualValue())
            .append(".bin"),
        output);
}

void DavScriptCompiler::useNamespace(const Token& namespaceName) {
    if (!DAVSCRIPT_LIBRARIES.contains(namespaceName.getActualValue())) {
        return;
    }

    const auto& registeredSymbols =
        DAVSCRIPT_LIBRARIES.at(namespaceName.getActualValue())
            .registeredSymbols;

    for (const auto& [symbolName, symbol] : registeredSymbols) {
        if (symbol->getSymbolType() == SymbolType::FUNCTION) {
            const auto functionSymbol =
                symbol->castToSymbolType<DavScriptFunctionSymbol>();

            m_RegisteredLibraryFunctions.emplace(
                functionSymbol->getFunctionPtr(),
                std::pair{Console::fmtTxt(namespaceName.getActualValue(), ".",
                                          symbolName),
                          functionSymbol->getFunction()});
        }
    }
}

uint32_t
DavScriptCompiler::registerVariableScope(std::string_view variableName) {
    m_VariableScopes.emplace_back(variableName.data(), m_CurrentScopeDepth);
    return static_cast<uint32_t>(m_VariableScopes.size() - 1);
}

bool DavScriptCompiler::canAccessVariable(std::string_view variableName) const {
    for (int i = static_cast<int>(m_VariableScopes.size()) - 1; i >= 0; i--) {
        if (m_VariableScopes.at(i).variableName == variableName) {
            return true;
        }
    }

    return false;
}

std::vector<uint8_t>
DavScriptCompiler::determineFunctionPtr(const Token& functionName) {
    int functionPtr = -1;
    for (const auto& registeredLibraryFunction : m_RegisteredLibraryFunctions) {
        if (registeredLibraryFunction.second.first ==
            functionName.getActualValue()) {
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

void DavScriptCompiler::logInvalidValueTypeError(const Token& typeToken,
                                                 ValueType    expectedType) {
    m_CompilerErrorMessages.push_back(
        DavScriptErrorFormatter::generateCompilerErrorInvalidValueType(
            typeToken, expectedType));
}

void DavScriptCompiler::logFoundAmbiguousFunctionError(
    const Token& functionName) {
    m_CompilerErrorMessages.push_back(
        DavScriptErrorFormatter::generateCompilerErrorFoundAmbiguousFunction(
            functionName));
}

void DavScriptCompiler::enterScope() { m_CurrentScopeDepth++; }

void DavScriptCompiler::exitScope() {
    m_CurrentScopeDepth--;

    for (int i = 0; i < m_VariableScopes.size(); i++) {
        if (m_VariableScopes.at(i).scopeDepth > m_CurrentScopeDepth) {
            m_VariableScopes.erase(m_VariableScopes.begin() + i);
        }
    }
}

void DavScriptCompiler::checkForCompilationErrors() const {
    if (m_CompilerErrorMessages.empty()) {
        return;
    }

    std::stringstream errorOutput;
    errorOutput << std::endl;

    for (std::string_view errorMessage : m_CompilerErrorMessages) {
        errorOutput << errorMessage.data() << std::endl;
    }

    errorOutput << std::endl;

    throw std::runtime_error(
        Console::fmtErr("DavScript failed during compilation!",
                        errorOutput.str(), m_CompilerErrorMessages.size(),
                        " error(s) occurred during the compilation phase."));
}
} // namespace davincpp::davscript
