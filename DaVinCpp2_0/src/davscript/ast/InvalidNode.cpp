#include "InvalidNode.h"
#include <stdexcept>

namespace davincpp::davscript
{
    bool InvalidNode::operator==(const AstNode& other) const
    {
        return dynamic_cast<const InvalidNode*>(&other) != nullptr;
    }

    std::vector<char> InvalidNode::generateByteCode()
    {
        throw std::runtime_error("Invalid node");
    }
}
