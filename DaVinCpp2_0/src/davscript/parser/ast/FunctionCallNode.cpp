#include "FunctionCallNode.h"
#include <execution/DavScriptCompiler.h>
#include <execution/ByteOperations.h>

#include <utility>
#include <parser/ast/ValueNode.h>

namespace davincpp::davscript
{
    FunctionCallNode::FunctionCallNode(
        Token functionName,
        const std::vector<std::shared_ptr<AstNode>>& parameters
    ) : m_FunctionName(std::move(functionName)),
        m_Parameters(parameters)
    { }

    [[nodiscard]] Token FunctionCallNode::getFunctionName() const
    {
        return m_FunctionName;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<AstNode>>& FunctionCallNode::getParameters() const
    {
        return m_Parameters;
    }

    std::vector<uint8_t> FunctionCallNode::generateByteCode(DavScriptCompiler* compiler)
    {
        std::vector<uint8_t> byteCode;

        std::vector<uint8_t> functionPtr = compiler->determineFunctionPtr(m_FunctionName);
        std::vector<uint8_t> parametersByteCode;

        for (const auto& parameter: m_Parameters) {
            if (auto valueNode = std::dynamic_pointer_cast<ValueNode>(parameter)) {
                Token valueType = valueNode->getValueType();
                std::vector<uint8_t> valueBytes = valueNode->generateByteCode(compiler, valueType);

                switch (valueType.getTokenType()) {
                    case INTTYPE: parametersByteCode.push_back(MOV_INT); break;
                    case BOOLTYPE: parametersByteCode.push_back(MOV_BOOL); break;
                    case FLOATTYPE: parametersByteCode.push_back(MOV_FLOAT); break;
                    case STRINGTYPE: parametersByteCode.push_back(MOV_STRING); break;
                    default: continue;
                }

                parametersByteCode.insert(parametersByteCode.end(), valueBytes.begin(), valueBytes.end());
            }
        }

        byteCode.insert(byteCode.begin(), parametersByteCode.begin(), parametersByteCode.end());
        byteCode.push_back(CALL);
        byteCode.insert(byteCode.end(), functionPtr.begin(), functionPtr.end());

        return byteCode;
    }

    bool FunctionCallNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const FunctionCallNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        if (m_FunctionName != otherNode->m_FunctionName) {
            return false;
        }

        if (m_Parameters.size() != otherNode->m_Parameters.size()) {
            return false;
        }

        for (size_t i = 0; i < m_Parameters.size(); i++) {
            if (*m_Parameters[i] != *otherNode->m_Parameters[i]) {
                return false;
            }
        }

        return true;
    }
}
