#pragma once
#include <memory>
#include <parser/ast/AstNode.h>

namespace davincpp::davscript
{
    class CallStackNode : public AstNode
    {
    public:
        void addNode(const std::shared_ptr<AstNode>& node);

        [[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& getCallStack() const;

        std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;
        [[nodiscard]] bool operator==(const AstNode& other) const override;

    protected:
        std::vector<std::shared_ptr<AstNode>> m_CallStack;
    };
}
