#include "AssignmentNode.h"

#include <DaVinCppString.h>
#include <execution/ByteCastHelper.h>
#include <execution/ByteOperations.h>
#include <execution/DavScriptCompiler.h>
#include <parser/ast/ValueNode.h>
#include <utility>

namespace davincpp::davscript {
AssignmentNode::AssignmentNode(Token variableType, Token identifier,
                               std::shared_ptr<ValueTypeNode> type,
                               std::shared_ptr<AstNode>       value)
    : m_VariableType(std::move(variableType)),
      m_Identifier(std::move(identifier)), m_Value(std::move(value)),
      m_Type(std::move(type)) {}

bool AssignmentNode::operator==(const AstNode& other) const {
    const auto* otherNode = dynamic_cast<const AssignmentNode*>(&other);
    if (otherNode == nullptr) {
        return false;
    }

    return m_VariableType == otherNode->m_VariableType &&
           m_Identifier == otherNode->m_Identifier &&
           *m_Type == *otherNode->m_Type && *m_Value == *otherNode->m_Value;
}

Token AssignmentNode::getVariableType() const { return m_VariableType; }

Token AssignmentNode::getIdentifier() const { return m_Identifier; }

std::shared_ptr<ValueTypeNode> AssignmentNode::getType() const {
    return m_Type;
}

std::shared_ptr<AstNode> AssignmentNode::getValue() const { return m_Value; }

std::vector<uint8_t>
AssignmentNode::generateByteCode(DavScriptCompiler* compiler) {
    std::vector<uint8_t> byteCode;

    Value staticValue;
    staticValue.data.object_t = nullptr;

    uint8_t              storeByteOperation = NUL;
    std::vector<uint8_t> valueBytes{};

    if (const auto valueNode = std::dynamic_pointer_cast<ValueNode>(m_Value)) {
        valueBytes = valueNode->generateByteCode(compiler, m_Type->getType());

        switch (m_Type->getType().getTokenType()) {
            case INTTYPE: {
                storeByteOperation = ST_INT;
                break;
            }
            case BOOLTYPE: {
                storeByteOperation = ST_BOOL;
                break;
            }
            case FLOATTYPE: {
                storeByteOperation = ST_FLOAT;
                break;
            }
            case STRINGTYPE: {
                storeByteOperation = ST_STRING;
                break;
            }
            case MIXEDTYPE:
                storeByteOperation = NUL;
                break;
            default:
                compiler->logInvalidValueTypeError(m_Type->getType(),
                                                   ValueType::OBJECT);
                return {};
        }
    }

    uint32_t variablePtr =
        compiler->registerVariableScope(m_Identifier.getActualValue());
    std::vector<uint8_t> variablePtrBytes =
        ByteCastHelper::nativeToBytes(variablePtr);

    byteCode.push_back(storeByteOperation);
    byteCode.insert(byteCode.end(), variablePtrBytes.begin(),
                    variablePtrBytes.end());
    byteCode.insert(byteCode.end(), valueBytes.begin(), valueBytes.end());

    return byteCode;
}
} // namespace davincpp::davscript
