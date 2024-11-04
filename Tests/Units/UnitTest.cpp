#include "UnitTest.h"

namespace davincpp::unittest
{
    UnitTest::UnitTest(std::string_view testName)
        : m_TestName(testName)
    { }

    UnitTest::~UnitTest() = default;


    std::string UnitTest::getTestName() const
    {
        return m_TestName;
    }
}
