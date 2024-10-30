#pragma once
#include <string>
#include <DaVinCppExceptions.h>
#include <Console.h>
#include <DaVinCppMacros.h>

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

#define assertTestStep(test) \
    try { test; } \
    catch (std::exception& exception) { \
        DEBUG_BREAK; \
        throw std::runtime_error( \
            davincpp::Console::fmtTxt("\nTest step '", #test, "' failed: \n", exception.what()) \
        ); \
    }

#define assertTrue(expression) \
    if (!(expression)) { \
        DEBUG_BREAK; \
        throw davincpp::system_error(davincpp::Console::fmtTxt( \
            "Failed to assert that the expression is true! \n\n\tExpression: '", #expression, "' was '", expression, "' \n\tFailed assertion at (", __FILE__, ":", __LINE__, ")") \
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
