#pragma once
#include <Console.h>
#include <DaVinCppExceptions.h>
#include <DaVinCppMacros.h>
#include <filesystem>
#include <functional>
#include <string>
#include <TestResult.h>
#include <TestStep.h>

namespace davincpp::unittest {
    class UnitTest
    {
    public:
        explicit UnitTest(std::string_view testName);
        virtual ~UnitTest();

        virtual void onSetup() noexcept = 0;
        void execute();
        virtual void onCleanUp() noexcept { }

        [[nodiscard]] std::string getTestName() const;
        [[nodiscard]] int getTestStepCount() const;
        [[nodiscard]] const std::vector<TestResult>& getTestResult() const;

    protected:
        void registerTestStep(const TestStep& testStep);

        void expectException(std::string_view expectedException);
        void expectException(const std::filesystem::path& expectedExceptionTranscript);

        void suppressConsoleOutput();
        std::string readSuppressedConsoleOutput() const;
        void restoreConsoleOutput();

    protected:
        std::string m_ExpectedException;

    private:
        std::vector<TestStep> m_TestSteps;
        std::vector<TestResult> m_TestResults;
        std::string m_TestName;

        bool m_ConsoleOutputSuppressed = false;
        std::stringstream m_SuppressedOutputBuffer;
        std::streambuf* m_OriginalOutputBuffer = nullptr;
    };

#define assertTrue(expression) \
    if (!(expression)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error(davincpp::Console::fmtTxt( \
            "Failed to assert that the expression is true! \n\n\tExpression: '", #expression, "' was ", expression ? "true" : "false", " \n\tFailed assertion at (", __FILE__, ":", __LINE__, ")") \
        ); \
    }

#define assertEquals(expected, actual) \
    if ((expected) != (actual)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error( \
            davincpp::Console::fmtTxt("Failed to assert that '", actual, "' equals '", expected, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")") \
        ); \
    }

#define assertGreaterThan(actual, number) \
    if ((actual) <= (number)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error( \
            davincpp::Console::fmtTxt("Failed to assert that '", actual, "' is greater than '", number, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")") \
        ); \
    }

#define assertLessThan(actual, number) \
    if ((actual) >= (number)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error( \
            davincpp::Console::fmtTxt("Failed to assert that '", actual, "' is less than '", number, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")") \
        ); \
    }

#define assertGreaterEqualsThan(actual, number) \
    if ((actual) < (number)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error( \
            davincpp::Console::fmtTxt("Failed to assert that '", actual, "' is greater or equal than '", number, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")") \
        ); \
    }

#define assertLessEqualsThan(actual, number) \
    if ((actual) > (number)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error( \
            davincpp::Console::fmtTxt("Failed to assert that '", actual, "' is less or equal than '", number, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")") \
        ); \
    }

#define assertGetException(expression, errorMsg) \
    { \
        bool thrownException = false; \
        try { expression; } \
        catch (std::exception& exception) { \
            std::string actualException = exception.what(); \
            assertEquals(std::string(errorMsg), actualException); \
            thrownException = true; \
        } \
        if (!thrownException) { \
            DEBUG_BREAK; \
            throw davincpp::system_error( \
                davincpp::Console::fmtTxt("Failed to assert that '", #expression, "' will throw the following exception: '", errorMsg, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")") \
            ); \
        } \
    }
}

