#include "UnitTest.h"

#include <DaVinCppFileSystem.h>

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

    void UnitTest::expectException(std::string_view expectedException)
    {
        m_ExpectedException = expectedException;
    }

    void UnitTest::expectException(const std::filesystem::path& expectedExceptionTranscript)
    {
        m_ExpectedException = DaVinCppFileSystem::readFile(expectedExceptionTranscript);
    }
}
