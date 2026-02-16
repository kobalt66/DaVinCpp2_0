#include "AssignmentNode.h"

#include <utility>
#include <ast/ValueNode.h>
#include <interpreter/ByteOperations.h>
#include <interpreter/DavScriptInterpreter.h>

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

    std::vector<uint8_t> AssignmentNode::generateByteCode(DavScriptInterpreter* interpreter)
    {
        StackValue staticValue(StackValueType::NONE, {});
        staticValue.data.object_t = nullptr;

        uint8_t storeByteOperation = NUL;

        if (const auto valueNode = std::dynamic_pointer_cast<ValueNode>(m_Value)) {
            std::string actualValue = valueNode->getValue().getActualValue();

            switch (m_Type->getType().getTokenType()) {
                case INTTYPE:
                    staticValue.type = StackValueType::INT;
                    staticValue.data.int_t = std::stoi(actualValue);
                    storeByteOperation = ST_INT;
                    break;
                case BOOLTYPE:
                    staticValue.type = StackValueType::BOOL;
                    staticValue.data.bool_t = actualValue == T_TRUE;
                    storeByteOperation = ST_BOOL;
                    break;
                case FLOATTYPE:
                    staticValue.type = StackValueType::DOUBLE;
                    staticValue.data.double_t = std::stod(actualValue);
                    storeByteOperation = ST_DOUBLE;
                    break;
                case STRINGTYPE:
                    staticValue.type = StackValueType::STRING;
                    staticValue.data.object_t = const_cast<char*>(actualValue.c_str());
                    storeByteOperation = ST_STRING;
                    break;
                case MIXEDTYPE:
                    staticValue.type = StackValueType::OBJECT;
                    staticValue.data.object_t = nullptr;
                    storeByteOperation = NUL;
                    break;
                default:
                    interpreter->logCompilerErrorInvalidValueType(m_Type->getType(), StackValueType::OBJECT);
                    return { };
            }
        }

        uint8_t ptr = interpreter->registerRuntimeConstant(staticValue);

        std::vector bytecode = {
            storeByteOperation,
            ptr,
        };

        return bytecode;
    }
}

