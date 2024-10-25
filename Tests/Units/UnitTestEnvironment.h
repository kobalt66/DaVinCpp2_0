#pragma once
#include <vector>
#include <memory>
#include <UnitTest.h>

namespace davincpp::unittest
{
    class UnitTestEnvironment
    {
    public:
        void addUnitTest(std::unique_ptr<UnitTest> unitTest);
        void execute();

    private:
        std::vector<std::unique_ptr<UnitTest>> m_AvailableTests;
    };
}
