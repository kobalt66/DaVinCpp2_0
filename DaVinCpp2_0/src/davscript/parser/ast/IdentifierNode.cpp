#include "IdentifierNode.h"

#include <Console.h>
#include <DaVinCppString.h>
#include <utility>
#include <error/DavScriptException.h>

namespace davincpp::davscript
{
    IdentifierNode::IdentifierNode(Token name)
        : m_Name(std::move(name))
    {
        m_NameSegments = DaVinCppString::split(m_Name.getActualValue(), '.');
    }

    void IdentifierNode::setName(std::string_view name)
    {
        m_Name.setActualValue(name);
        m_NameSegments = DaVinCppString::split(name, '.');
    }

    Token IdentifierNode::getName() const
    {
        return m_Name;
    }

    size_t IdentifierNode::getNameSegCount() const
    {
        return m_NameSegments.size();
    }

    Token IdentifierNode::getFullParentSeg() const
    {
        if (m_NameSegments.empty()) {
            throw DavScriptException("Invalid identifier caught: Identifier is empty");
        }

        size_t lastSegIndex = m_NameSegments.size() - 1;

        std::string parentSeg;
        for (size_t i = 0; i < lastSegIndex; i++) {
            parentSeg += m_NameSegments.at(i);

            if (i != lastSegIndex - 1) {
                parentSeg += ".";
            }
        }

        Token segToken = m_Name;
        segToken.setActualValue(parentSeg);
        return segToken;
    }

    Token IdentifierNode::getLastNameSeg() const
    {
        if (m_NameSegments.empty()) {
            throw DavScriptException("Invalid identifier caught: Identifier is empty");
        }

        size_t lastSegIndex = m_NameSegments.size() - 1;
        std::string nameSeg = m_NameSegments.at(lastSegIndex);

        CharPosition segPosition = m_Name.getTokenPosition();
        for (size_t i = 0; i < lastSegIndex; i++) {
            segPosition.incrementCharIdx(static_cast<int>(m_NameSegments.at(i).size() + 1));
        }

        Token segToken = m_Name;
        segToken.setActualValue(nameSeg);
        return segToken;
    }

    bool IdentifierNode::operator==(const AstNode& other) const
    {
        const auto* otherNode = dynamic_cast<const IdentifierNode*>(&other);
        if (otherNode == nullptr) {
            return false;
        }

        return m_Name == otherNode->m_Name;
    }

    std::vector<uint8_t> IdentifierNode::generateByteCode(DavScriptCompiler* compiler)
    {
        return {};
    }
}
