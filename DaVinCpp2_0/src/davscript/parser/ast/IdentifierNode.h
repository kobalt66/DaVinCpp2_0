#pragma once
#include <string>
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

namespace davincpp::davscript
{
    class IdentifierNode final : public AstNode
    {
    public:
        explicit IdentifierNode(Token name);

        void setName(std::string_view name);
        [[nodiscard]] Token getName() const;

        [[nodiscard]] size_t getNameSegCount() const;
        [[nodiscard]] Token getFullParentSeg() const;
        [[nodiscard]] Token getLastNameSeg() const;

        [[nodiscard]] bool operator==(const AstNode& other) const override;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;

    private:
        std::vector<std::string> m_NameSegments;
        Token m_Name;
    };
}
