#include "FunctionCallNode.h"
#include <execution/DavScriptCompiler.h>
#include <execution/ByteOperations.h>

#include <utility>

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

        byteCode.push_back(CALL);

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
