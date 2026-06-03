#include "UnitTestEnvironment.h"

#include <Console.h>
#include <DaVinCppString.h>
#include <Timer.h>

namespace davincpp::unittest {
void UnitTestEnvironment::addUnitTest(std::unique_ptr<UnitTest> unitTest) {
    m_AvailableTests.emplace_back(std::move(unitTest));
}

void UnitTestEnvironment::execute() {
    Timer timer;

    int totalTestStepCount = 0;
    for (const auto& unitTest : m_AvailableTests) {
        unitTest->onSetup();
        totalTestStepCount += unitTest->getTestStepCount();
    }

    Console::raw(Console::GREEN, "Executing unit tests...");
    Console::raw(Console::GREEN, "---------------------------------------------"
                                 "---------------------------------");
    Console::raw(Console::GRAY,
                 Console::fmtTxt("Available tests: ", totalTestStepCount));
    Console::raw(Console::GREEN, "---------------------------------------------"
                                 "---------------------------------");
    Console::newline();

    timer.start();

    int testVisualCounter             = 0;
    int executedUnitTestCount         = 0;
    int successfullyExecutedTestCount = 0;

    const auto lineWrapper = [&totalTestStepCount, &executedUnitTestCount,
                              &testVisualCounter] {
        if (++testVisualCounter == 60) {
            std::cout << " (" << executedUnitTestCount << " / "
                      << totalTestStepCount << ")";
            Console::newline();
            testVisualCounter = 0;
        }
    };

    std::vector<std::pair<std::string, std::runtime_error>> errors;

    for (const std::unique_ptr<UnitTest>& unitTest : m_AvailableTests) {
        try {
            assertTestCall(unitTest->execute());
            assertTestCall(unitTest->onCleanUp());

            for (const auto& testResult : unitTest->getTestResult()) {
                successfullyExecutedTestCount++;
                executedUnitTestCount++;

                if (testResult.success) {
                    std::cout << ".";
                    lineWrapper();
                    continue;
                }

                errors.emplace_back(unitTest->getTestName(),
                                    testResult.errorMsg);
                std::cout << Console::fmtRaw(Console::RED, "E");
                lineWrapper();
            }
        } catch (std::runtime_error& exception) {
            executedUnitTestCount++;

            errors.emplace_back(unitTest->getTestName(), exception);
            std::cout << Console::fmtRaw(Console::RED, "F");
            ;
            lineWrapper();
        }
    }

    Console::newline();
    Console::newline();

    timer.stop();

    Console::raw(Console::GREEN, "---------------------------------------------"
                                 "---------------------------------");
    Console::raw(Console::GREEN, "Finished executing all unit tests!");
    Console::newline();

    if (errors.empty()) {
        Console::raw(Console::GREEN, "OK");
    } else {
        Console::raw(Console::RED, "ERRORS found:");

        for (std::pair<std::string, std::runtime_error>& error : errors) {
            Console::newline();
            Console::raw(Console::RED, "In test ('", error.first, "')");
            Console::raw(Console::RED,
                         "-----------------------------------------------------"
                         "-------------------------");
            Console::raw(Console::RED, error.second.what());
            Console::raw(Console::RED,
                         "-----------------------------------------------------"
                         "-------------------------");
        }
    }

    Console::newline();
    Console::raw(Console::GRAY, Console::fmtTxt("Total execution time: ",
                                                DaVinCppString::fmtTime(
                                                    timer.fetchTimeMsc())));
    Console::raw(Console::GRAY, Console::fmtTxt("Successfully executed tests: ",
                                                successfullyExecutedTestCount,
                                                "/", totalTestStepCount));
}
} // namespace davincpp::unittest
