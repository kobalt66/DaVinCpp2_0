#include "ValueNode.h"
#include <utility>

namespace davincpp::davscript
{
    ValueNode::ValueNode(Token value)
        : m_Value(std::move(value))
    { }

    bool ValueNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const ValueNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        return m_Value == otherNode->m_Value;
    }

    Token ValueNode::getValue() const
    {
        return m_Value;
    }
}
