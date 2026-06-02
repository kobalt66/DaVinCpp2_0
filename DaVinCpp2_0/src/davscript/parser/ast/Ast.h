#pragma once
#include <parser/ast/CallStackNode.h>
#include <parser/ast/IdentifierNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
class Ast final : public CallStackNode
{
public:
    Ast() = default;
    explicit Ast(IdentifierNode script);

    [[nodiscard]] bool operator==(const AstNode& other) const override;

    std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

    [[nodiscard]] IdentifierNode getModuleNamespace() const;

private:
    IdentifierNode m_ModuleNamespace;
};
}  // namespace davincpp::davscript
