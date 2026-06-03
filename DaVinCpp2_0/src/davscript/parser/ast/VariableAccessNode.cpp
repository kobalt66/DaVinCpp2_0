#include "VariableAccessNode.h"

namespace davincpp::davscript {
VariableAccessNode::VariableAccessNode(Token variableName)
    : m_VariableName(std::move(variableName)) {}

Token VariableAccessNode::getVariableName() const { return m_VariableName; }

bool VariableAccessNode::operator==(const AstNode& other) const {
    const auto* otherNode = dynamic_cast<const VariableAccessNode*>(&other);
    if (otherNode == nullptr) {
        return false;
    }

    return m_VariableName == otherNode->m_VariableName;
}

std::vector<uint8_t>
VariableAccessNode::generateByteCode(DavScriptCompiler* compiler) {
    return {};
}
} // namespace davincpp::davscript
