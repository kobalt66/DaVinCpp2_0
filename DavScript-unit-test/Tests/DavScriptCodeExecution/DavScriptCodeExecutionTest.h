#pragma once
#include <UnitTest.h>

namespace davincpp::davscript
{
    class DavScriptCodeExecutionTest final : public unittest::UnitTest
    {
    public:
        explicit DavScriptCodeExecutionTest();

        void execute() override;

    private:
        static void testVariableAssignment();
    };
}
