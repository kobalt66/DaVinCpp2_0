#include "Ast.h"

namespace davincpp::davscript
{
    bool Ast::operator==(const AstNode& other) const
    {
        const auto* otherAst = dynamic_cast<const Ast*>(&other);
        if (otherAst == nullptr) {
            return false;
        }

        if (m_EntryPoint != otherAst->m_EntryPoint) {
            return false;
        }

        if (m_FunctionIndexMap != otherAst->m_FunctionIndexMap) {
            return false;
        }

        return CallStackNode::operator==(other);
    }

    std::vector<char> Ast::generateByteCode()
    {
        return {};
    }

    int Ast::getEntryPoint() const
    {
        return m_EntryPoint;
    }

    const std::unordered_map<std::string, int>& Ast::getFunctionIndexMap() const
    {
        return m_FunctionIndexMap;
    }
}
