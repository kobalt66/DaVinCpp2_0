#include "InvalidNode.h"

#include <execution/DavScriptCompiler.h>
#include <stdexcept>

namespace davincpp::davscript {
bool InvalidNode::operator==(const AstNode& other) const {
    return dynamic_cast<const InvalidNode*>(&other) != nullptr;
}

std::vector<uint8_t>
InvalidNode::generateByteCode(DavScriptCompiler* compiler) {
    throw std::runtime_error("Invalid node");
}
} // namespace davincpp::davscript
