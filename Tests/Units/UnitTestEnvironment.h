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

#define assertTestCall(call) \
    try { call; } \
    catch (std::exception& exception) { \
        std::string callName = DaVinCppString::split(#call, '>').at(1); \
        throw std::runtime_error(Console::fmtTxt("Error occured on the test call called '", callName, "': \n", exception.what()));\
    }
}
