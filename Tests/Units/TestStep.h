#pragma once
#include <bits/ranges_util.h>
#include <functional>
#include <string>

namespace davincpp::unittest {
struct TestStep {
    std::string           name;
    std::function<void()> testStep;

    bool operator==(const TestStep& other) const;
    bool operator!=(const TestStep& other) const;
};
} // namespace davincpp::unittest
