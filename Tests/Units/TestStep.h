#pragma once
#include <functional>
#include <string>
#include <bits/ranges_util.h>

namespace davincpp::unittest
{
struct TestStep
{
    std::string           name;
    std::function<void()> testStep;

    bool operator==(const TestStep& other) const;
    bool operator!=(const TestStep& other) const;
};
}
