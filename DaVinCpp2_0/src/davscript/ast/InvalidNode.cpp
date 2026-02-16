#include "InvalidNode.h"
#include <stdexcept>
#include <interpreter/DavScriptInterpreter.h>

namespace davincpp::davscript
{
    bool InvalidNode::operator==(const AstNode& other) const
    {
        return dynamic_cast<const InvalidNode*>(&other) != nullptr;
    }

    std::vector<uint8_t> InvalidNode::generateByteCode(DavScriptInterpreter* interpreter)
    {
        throw std::runtime_error("Invalid node");
    }
}
