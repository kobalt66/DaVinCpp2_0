#pragma once
#include <string>
#include <DaVinCppExceptions.h>
#include <Console.h>

namespace davincpp::unittest {
    class UnitTest
    {
    public:
        explicit UnitTest(std::string_view testName);
        virtual ~UnitTest();

        virtual void onSetup() { }
        virtual void execute() = 0;
        virtual void onCleanUp() { }

        [[nodiscard]] std::string getTestName() const;

    private:
        std::string m_TestName;
    };

#define assertTrue(expression) \
    if (!expression) { \
        throw davincpp::system_error(davincpp::Console::fmtTxt( \
            "Failed to assert that the expression is true! \n\n\tExpression: '", #expression, "' was '", expression, "' \n\tFailed assertion at (", __FILE__, ":", __LINE__, ")")); \
    }

#define assertEquals(expected, actual) \
    if (expected != actual) { \
        throw davincpp::system_error(davincpp::Console::fmtTxt("Failed to assert that '", actual, "' equals '", expected, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")")); \
    }

#define assertGreaterThan(actual, number) \
    if (actual <= number) { \
        throw davincpp::system_error(davincpp::Console::fmtTxt("Failed to assert that '", actual, "' is greater than '", number, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")")); \
    }

#define assertLessThan(actual, number) \
    if (actual <= number) { \
        throw davincpp::system_error(davincpp::Console::fmtTxt("Failed to assert that '", actual, "' is less than '", number, "'! \nFailed assertion at (", __FILE__, ":", __LINE__, ")")); \
    }
}
