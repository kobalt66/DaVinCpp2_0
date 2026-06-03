#pragma once
#include <parser/ast/AstNode.h>

namespace davincpp::davscript {
class InvalidNode final : public AstNode {
  public:
    [[nodiscard]] bool operator==(const AstNode& other) const override;

    std::vector<uint8_t> generateByteCode(DavScriptCompiler* compiler) override;
};
} // namespace davincpp::davscript
