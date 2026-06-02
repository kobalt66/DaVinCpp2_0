#include "TestStep.h"

namespace davincpp::unittest
{
bool TestStep::operator==(const TestStep& other) const { return name == other.name; }

bool TestStep::operator!=(const TestStep& other) const { return !(*this == other); }
}
