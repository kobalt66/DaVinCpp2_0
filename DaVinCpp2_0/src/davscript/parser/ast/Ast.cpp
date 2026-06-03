#include "Ast.h"

#include <execution/ByteOperations.h>
#include <execution/DavScriptCompiler.h>
#include <utility>

namespace davincpp::davscript {
Ast::Ast(IdentifierNode moduleNamespace)
    : m_ModuleNamespace(std::move(moduleNamespace)) {}

bool Ast::operator==(const AstNode& other) const {
    const auto* otherAst = dynamic_cast<const Ast*>(&other);
    if (otherAst == nullptr) {
        return false;
    }

    return otherAst->m_ModuleNamespace == m_ModuleNamespace &&
           CallStackNode::operator==(other);
}

std::vector<uint8_t> Ast::generateByteCode(DavScriptCompiler* compiler) {
    std::vector<uint8_t> byteCode;

    for (const auto& node : m_CallStack) {
        std::vector<uint8_t> nodeByteCode = node->generateByteCode(compiler);
        byteCode.insert(byteCode.end(), nodeByteCode.begin(),
                        nodeByteCode.end());
    }

    byteCode.push_back(END);
    byteCode.push_back(NUL);
    return byteCode;
}

IdentifierNode Ast::getModuleNamespace() const { return m_ModuleNamespace; }
} // namespace davincpp::davscript
