#include "AssignmentNode.h"

#include <utility>

namespace davincpp::davscript
{
    AssignmentNode::AssignmentNode(
        Token variableType,
        Token identifier,
        std::shared_ptr<ValueTypeNode> type,
        std::shared_ptr<AstNode> value
    ) : m_VariableType(std::move(variableType)),
        m_Identifier(std::move(identifier)),
        m_Type(std::move(type)),
        m_Value(std::move(value))
    { }

    bool AssignmentNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const AssignmentNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        return
            m_VariableType == otherNode->m_VariableType &&
            m_Identifier == otherNode->m_Identifier &&
            *m_Type == *otherNode->m_Type &&
            *m_Value == *otherNode->m_Value;
    }

    Token AssignmentNode::getVariableType() const
    {
        return m_VariableType;
    }

    Token AssignmentNode::getIdentifier() const
    {
        return m_Identifier;
    }

    std::shared_ptr<ValueTypeNode> AssignmentNode::getType() const
    {
        return m_Type;
    }

    std::shared_ptr<AstNode> AssignmentNode::getValue() const
    {
        return m_Value;
    }
}

