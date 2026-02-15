#pragma once
#include <ast/AstNode.h>
#include <memory>

namespace davincpp::davscript
{
    class CallStackNode : public AstNode
    {
    public:
        [[nodiscard]] bool operator==(const AstNode& other) const override;

        void addNode(const std::shared_ptr<AstNode>& node);

        std::vector<char> generateByteCode() override { return {}; }

        [[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& getCallStack() const;

    private:
        std::vector<std::shared_ptr<AstNode>> m_CallStack;
    };
}
