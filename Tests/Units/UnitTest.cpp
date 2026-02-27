#include "UnitTest.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppString.h>

namespace davincpp::unittest
{
    UnitTest::UnitTest(std::string_view testName)
        : m_TestName(testName)
    { }

    UnitTest::~UnitTest() = default;

    void UnitTest::execute()
    {
        for (const auto& [testStepName, testStep] : m_TestSteps) {
            try {
                testStep();
            }
            catch (std::exception& exception) {
                if (!m_ExpectedException.empty()) {
                    std::string actualException = DaVinCppString::findReplaceAllByRegex(exception.what(), std::regex(R"(\x1B\[[0-9;]*m|033\[[0-9;]*m)"), "");

                    if (m_ExpectedException == actualException) {
                        m_ExpectedException.clear();
                        return;
                    }

                    std::string failedTestDescription = Console::fmtTxt(
                        "\nTest step '", "testAssignmentNodeFailure()", "' failed: \n", "Expected exception was not thrown: \n",
                        "Actual exception: \n", actualException, "........................................\n",
                        "Expected exception: \n", m_ExpectedException);

                    m_ExpectedException.clear();
                    m_TestResults.emplace_back(false, failedTestDescription);
                    DEBUG_BREAK;
                    continue;
                }

                m_TestResults.emplace_back(false, Console::fmtTxt("\nTest step '", testStepName, "' failed: \n", exception.what()));
                DEBUG_BREAK;
                continue;
            }

            m_TestResults.emplace_back(true, "");
        }
    }

    std::string UnitTest::getTestName() const
    {
        return m_TestName;
    }

    const std::vector<TestResult>& UnitTest::getTestResult() const
    {
        return m_TestResults;
    }

    void UnitTest::registerTestStep(const std::string& testStepName, const std::function<void()>& testStep)
    {
        m_TestSteps.emplace(testStepName, testStep);
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
