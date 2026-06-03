#include "UnitTest.h"

#include <DaVinCppFileSystem.h>
#include <DaVinCppString.h>
#include <ranges>

namespace davincpp::unittest {
UnitTest::UnitTest(std::string_view testName) : m_TestName(testName) {}

UnitTest::~UnitTest() = default;

void UnitTest::execute() {
    for (const auto& [testStepName, testStep] : m_TestSteps) {
        try {
            testStep();
        } catch (std::exception& exception) {
            restoreConsoleOutput();
            if (!m_ExpectedException.empty()) {
                std::string actualException =
                    Console::cleanseText(exception.what());

                if (m_ExpectedException == actualException) {
                    m_TestResults.emplace_back(true, "");
                    m_ExpectedException.clear();
                    continue;
                }

                std::string failedTestDescription = Console::fmtTxt(
                    "\nTest step '", "testAssignmentNodeFailure()",
                    "' failed: \n", "Expected exception was not thrown: \n",
                    "Actual exception: \n", actualException,
                    "\n........................................\n",
                    "Expected exception: \n", m_ExpectedException);

                m_ExpectedException.clear();
                m_TestResults.emplace_back(false, failedTestDescription);
                DEBUG_BREAK;
                continue;
            }

            m_TestResults.emplace_back(
                false, Console::fmtTxt("\nTest step '", testStepName,
                                       "' failed: \n", exception.what()));
            DEBUG_BREAK;
            continue;
        }

        m_TestResults.emplace_back(true, "");
    }
}

std::string UnitTest::getTestName() const { return m_TestName; }

int UnitTest::getTestStepCount() const {
    return static_cast<int>(m_TestSteps.size());
}

const std::vector<TestResult>& UnitTest::getTestResult() const {
    return m_TestResults;
}

void UnitTest::registerTestStep(const TestStep& testStep) {
    if (std::ranges::find(m_TestSteps, testStep) != m_TestSteps.end()) {
        throw std::runtime_error(
            Console::fmtErr("Test step '", testStep.name, "' already exists!"));
    }

    m_TestSteps.push_back(testStep);
}

void UnitTest::expectException(std::string_view expectedException) {
    m_ExpectedException = expectedException;
}

void UnitTest::expectException(
    const std::filesystem::path& expectedExceptionTranscript) {
    m_ExpectedException =
        DaVinCppFileSystem::readFile(expectedExceptionTranscript);
}

void UnitTest::suppressConsoleOutput() {
    m_ConsoleOutputSuppressed = true;
    m_OriginalOutputBuffer = std::cout.rdbuf(m_SuppressedOutputBuffer.rdbuf());
}

std::string UnitTest::readSuppressedConsoleOutput() const {
    return Console::cleanseText(m_SuppressedOutputBuffer.str());
}

void UnitTest::restoreConsoleOutput() {
    if (!m_ConsoleOutputSuppressed) {
        return;
    }

    std::cout.rdbuf(m_OriginalOutputBuffer);
    m_ConsoleOutputSuppressed = false;
}
} // namespace davincpp::unittest
