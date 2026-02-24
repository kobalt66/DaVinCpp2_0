#pragma once
#include <memory>
#include <ast/Ast.h>
#include <execution/dto/Value.h>
#include <execution/dto/VariableScope.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class DavScriptCompiler final
    {
    public:
        explicit DavScriptCompiler(std::shared_ptr<Ast> ast);

        void reset();
        std::vector<uint8_t> compile();

        uint8_t registerVariableScope(std::string_view variableName);
        [[nodiscard]] bool canAccessVariable(std::string_view variableName) const;

        [[nodiscard]] uint32_t registerRuntimeConstant(Value value);

        [[nodiscard]] const std::vector<Value>& getRuntimeConstantsPool() const;

        void logCompilerErrorInvalidValueType(const Token& typeToken, ValueType expectedType);

    private:
        void enterScope();
        void exitScope();

        void checkForCompilationErrors() const;

    private:
        std::shared_ptr<Ast> m_Ast;

        std::vector<VariableScope> m_VariableScopes;
        int m_CurrentScopeDepth = 0;

        std::vector<Value> m_RuntimeConstantsPool;

        std::vector<std::string> m_CompilerErrorMessages;
    };
}
