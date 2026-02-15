#pragma once
#include <string>

namespace davincpp::davscript
{
    struct StackValue
    {
        void* value = nullptr;
        std::string type;
    };
}
