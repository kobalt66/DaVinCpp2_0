#include "UseNode.h"

#include <utility>

namespace davincpp::davscript
{
    UseNode::UseNode(Token namespacedName)
        : m_NamespacedName(std::move(namespacedName))
    { }

    Token UseNode::getNamespaceName() const
    {
        return m_NamespacedName;
    }

    bool UseNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const UseNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        return m_NamespacedName == otherNode->m_NamespacedName;
    }

    std::vector<uint8_t> UseNode::generateByteCode(DavScriptCompiler* compiler)
    {
        return {};
    }
}
