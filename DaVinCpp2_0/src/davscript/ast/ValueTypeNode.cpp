#include "ValueTypeNode.h"

#include <utility>

namespace davincpp::davscript
{
    ValueTypeNode::ValueTypeNode(Token type)
        : m_Type(std::move(type))
    { }

    bool ValueTypeNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const ValueTypeNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        return m_Type == otherNode->m_Type;
    }

    Token ValueTypeNode::getType() const
    {
        return m_Type;
    }
}
