#pragma once
#include <stdexcept>
#include <string>

namespace davincpp::davscript
{
    class DavScriptException final : public std::runtime_error
    {
    public:
        explicit DavScriptException(const std::string& message);
    };
}
