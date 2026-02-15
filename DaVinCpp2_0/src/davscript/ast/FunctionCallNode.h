#pragma once
#include <ast/AstNode.h>
#include <tokens/Token.h>
#include <vector>
#include <memory>

namespace davincpp::davscript
{
    class FunctionCallNode final : public AstNode
    {
    public:
        FunctionCallNode(Token functionName, const std::vector<std::shared_ptr<AstNode>>& parameters);

        [[nodiscard]] Token getFunctionName() const;
        [[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& getParameters() const;

        std::vector<char> generateByteCode() override { return {}; }

    private:
        Token m_FunctionName;
        std::vector<std::shared_ptr<AstNode>> m_Parameters;
    };
}
