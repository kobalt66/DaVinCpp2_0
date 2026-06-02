#pragma once
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>
#include <vector>
#include <memory>

namespace davincpp::davscript
{
class FunctionCallNode final : public AstNode
{
public:
    FunctionCallNode(Token functionName, const std::vector<std::shared_ptr<AstNode>>& parameters);

    [[nodiscard]] Token                                        getFunctionName() const;
    [[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& getParameters() const;

    std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;
    [[nodiscard]] bool   operator==(const AstNode& other) const override;

private:
    Token                                 m_FunctionName;
    std::vector<std::shared_ptr<AstNode>> m_Parameters;
};
}  // namespace davincpp::davscript
