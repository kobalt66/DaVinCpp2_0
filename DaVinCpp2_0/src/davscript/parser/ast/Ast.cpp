#include "Ast.h"
#include <execution/ByteOperations.h>
#include <execution/DavScriptCompiler.h>

namespace davincpp::davscript
{
    bool Ast::operator==(const AstNode& other) const
    {
        const auto* otherAst = dynamic_cast<const Ast*>(&other);
        if (otherAst == nullptr) {
            return false;
        }

        return CallStackNode::operator==(other);
    }

    std::vector<uint8_t> Ast::generateByteCode(DavScriptCompiler* compiler)
    {
        std::vector<uint8_t> byteCode;

        for (const auto& node: m_CallStack) {
            std::vector<uint8_t> nodeByteCode = node->generateByteCode(compiler);
            byteCode.insert(byteCode.end(), nodeByteCode.begin(), nodeByteCode.end());
        }

        byteCode.push_back(END);
        byteCode.push_back(NUL);
        return byteCode;
    }
}
