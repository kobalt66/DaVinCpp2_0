#include "ValueNode.h"
#include <utility>
#include <execution/ByteCastHelper.h>
#include <execution/ByteOperations.h>
#include <execution/DavScriptCompiler.h>
#include <execution/dto/Value.h>

namespace davincpp::davscript
{
ValueNode::ValueNode(Token value)
    : m_Value(std::move(value))
{
}

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

Token ValueNode::getValueType() const
{
	Token valueType = m_Value;
	valueType.setTokenRole(VALUETYPE);

	switch (m_Value.getTokenType()) {
	case NUMBERINT:
		valueType.setTokenType(INTTYPE);
		break;
	case NUMBERFLOAT:
		valueType.setTokenType(FLOATTYPE);
		break;
	case STRING:
		valueType.setTokenType(STRINGTYPE);
		break;
	case TRUE:
	case FALSE:
		valueType.setTokenType(BOOLTYPE);
		break;
	default:
		valueType.setTokenType(MIXEDTYPE);
		break;
	}

	return valueType;
}

std::vector<uint8_t> ValueNode::generateByteCode(DavScriptCompiler* compiler, const Token& valueType) const
{
	std::vector<uint8_t> valueBytes;
	std::string actualValue = m_Value.getActualValue();

	switch (valueType.getTokenType()) {
	case INTTYPE: {
		valueBytes = ByteCastHelper::nativeToBytes(std::stol(actualValue));
		break;
	}
	case BOOLTYPE: {
		valueBytes = ByteCastHelper::nativeToBytes(actualValue == T_TRUE);
		break;
	}
	case FLOATTYPE: {
		valueBytes = ByteCastHelper::nativeToBytes(std::stod(actualValue));
		break;
	}
	case STRINGTYPE: {
		valueBytes = ByteCastHelper::stringToBytes(actualValue);
		valueBytes.push_back(NUL);
		break;
	}
	default:
		compiler->logInvalidValueTypeError(valueType, ValueType::OBJECT);
		return {};
	}

	return valueBytes;
}
} // namespace davincpp::davscript
