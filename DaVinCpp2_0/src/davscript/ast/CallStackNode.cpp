#include "CallStackNode.h"
#include <execution/DavScriptCompiler.h>

namespace davincpp::davscript
{
    bool CallStackNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const CallStackNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        if (m_CallStack.size() != otherNode->m_CallStack.size()) {
            return false;
        }

        for (size_t i = 0; i < m_CallStack.size(); i++) {
            if (*m_CallStack[i] != *otherNode->m_CallStack[i]) {
                return false;
            }
        }

        return true;
    }

    void CallStackNode::addNode(const std::shared_ptr<AstNode>& node)
    {
        m_CallStack.push_back(node);
    }

    std::vector<uint8_t> CallStackNode::generateByteCode(DavScriptCompiler* compiler)
    {
        std::vector<uint8_t> byteCode;

        for (const auto& node: m_CallStack) {
            std::vector<uint8_t> nodeByteCode = node->generateByteCode(compiler);
            byteCode.insert(byteCode.end(), nodeByteCode.begin(), nodeByteCode.end());
        }

        return byteCode;
    }

    const std::vector<std::shared_ptr<AstNode>>& CallStackNode::getCallStack() const
    {
        return m_CallStack;
    }
}
