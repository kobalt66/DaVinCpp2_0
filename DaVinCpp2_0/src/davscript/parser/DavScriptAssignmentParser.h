#pragma once
#include <parser/BaseNodeParser.h>

namespace davincpp::davscript
{
    class DavScriptAssignmentParser final : public BaseNodeParser
    {
    public:
        DavScriptAssignmentParser() = default;

        [[nodiscard]] std::shared_ptr<AstNode> parseNode(DavScriptParser* scriptParser) override;
    };
}
