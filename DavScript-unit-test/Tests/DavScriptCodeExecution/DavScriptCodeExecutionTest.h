#pragma once
#include <UnitTest.h>

namespace davincpp::davscript
{
    static auto PROJECT_DIRECTORY = "../Tests/DavScriptCodeExecution";

    class DavScriptCodeExecutionTest final : public unittest::UnitTest
    {
    public:
        explicit DavScriptCodeExecutionTest();

        void onSetup() noexcept override;

    private:
        static void testVariableAssignment();
        void testSimplePrintFunctionCall();
    };
}
