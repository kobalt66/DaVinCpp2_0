#pragma once
#include <cstdint>
#include <vector>

namespace davincpp::davscript
{
    class DavScriptInterpreter;

    class AstNode
    {
    public:
        AstNode() = default;
        virtual ~AstNode() = default;

        [[nodiscard]] virtual bool operator==(const AstNode& other) const = 0;
        [[nodiscard]] bool operator!=(const AstNode& other) const { return !(*this == other); }

        virtual std::vector<uint8_t> generateByteCode(DavScriptInterpreter* interpreter) = 0;
    };
}
