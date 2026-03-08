#pragma once
#include <string>

namespace davincpp::unittest
{
    struct TestResult
    {
        bool success;
        std::string errorMsg;
    };
}
