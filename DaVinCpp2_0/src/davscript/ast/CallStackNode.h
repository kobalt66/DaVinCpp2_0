#pragma once
#include <memory>
#include <ast/AstNode.h>

namespace davincpp::davscript
{
    class CallStackNode : public AstNode
    {
    public:
        [[nodiscard]] bool operator==(const AstNode& other) const override;

        void addNode(const std::shared_ptr<AstNode>& node);

        std::vector<uint8_t> generateByteCode(DavScriptInterpreter* interpreter) override;

        [[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& getCallStack() const;

    protected:
        std::vector<std::shared_ptr<AstNode>> m_CallStack;
    };
}
