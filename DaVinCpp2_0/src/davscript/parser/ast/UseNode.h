#pragma once
#include <string>
#include <string_view>
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class UseNode final : public AstNode
    {
    public:
        explicit UseNode(Token namespacedName);

        [[nodiscard]] Token getNamespaceName() const;

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

    private:
        Token m_NamespacedName;
    };
}
