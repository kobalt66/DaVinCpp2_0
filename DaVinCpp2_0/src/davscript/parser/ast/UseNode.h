#pragma once
#include <string>
#include <string_view>
#include <parser/ast/AstNode.h>

namespace davincpp::davscript
{
    class UseNode final : public AstNode
    {
    public:
        explicit UseNode(std::string namespacedName);

        [[nodiscard]] std::string getNamespaceName() const;

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

    private:
        std::string m_NamespacedName;
    };
}
