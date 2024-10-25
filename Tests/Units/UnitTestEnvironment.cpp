#include "UnitTestEnvironment.h"
#include <Console.h>
#include <DaVinCppString.h>
#include <Timer.h>

namespace davincpp::unittest
{
    void UnitTestEnvironment::addUnitTest(std::unique_ptr<UnitTest> unitTest)
    {
        m_AvailableTests.emplace_back(std::move(unitTest));
    }

    void UnitTestEnvironment::execute()
    {
        Timer timer;

        Console::raw(Console::GREEN, "Executing unit tests...");
        Console::raw(Console::GREEN, "------------------------------------------------------------------------------");
        Console::raw(Console::GRAY, Console::fmtTxt("Available tests: ", m_AvailableTests.size()));
        Console::raw(Console::GREEN, "------------------------------------------------------------------------------");
        Console::newline();

        timer.start();

        int unitTestCount = 0;
        int executedUnitTestCount = 0;
        int successfullyExecutedTestCount = 0;

        std::vector<std::pair<std::string, std::runtime_error>> errors;

        for (const std::unique_ptr<UnitTest>& unitTest : m_AvailableTests) {
            try {
                unitTest->onSetup();
                unitTest->execute();
                unitTest->onCleanUp();

                successfullyExecutedTestCount++;
                std::cout << ".";
            } catch (std::runtime_error& exeption) {
                errors.emplace_back(unitTest->getTestName(), exeption);
                std::cout << "E";
            }

            executedUnitTestCount++;

            if (++unitTestCount == 40) {
                std::cout << " (" << executedUnitTestCount << " / " << m_AvailableTests.size() << ")";
                Console::newline();
                unitTestCount = 0;
            }
        }

        Console::newline();
        Console::newline();

        timer.stop();

        Console::raw(Console::GREEN, "------------------------------------------------------------------------------");
        Console::raw(Console::GREEN, "Finished executing all unit tests!");
        Console::newline();

        if (errors.empty()) {
            Console::raw(Console::GREEN, "OK");
        } else {
            Console::raw(Console::RED, "ERRORS found:");

            for (std::pair<std::string, std::runtime_error>& error : errors) {
                Console::newline();
                Console::raw(Console::RED, "In test ('", error.first, "')");
                Console::raw(Console::RED, "------------------------------------------------------------------------------");
                Console::raw(Console::RED, error.second.what());
                Console::raw(Console::RED, "------------------------------------------------------------------------------");
            }
        }

        Console::newline();
        Console::raw(Console::GRAY, Console::fmtTxt("Total execution time: ", DaVinCppString::fmtTime(timer.fetchTimeMsc())));
        Console::raw(Console::GRAY, Console::fmtTxt("Successfully executed tests: ", successfullyExecutedTestCount, "/", executedUnitTestCount));
    }
}
