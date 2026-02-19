#pragma once
#include <UnitTest.h>

namespace davincpp::davscript
{
    class DavScriptInterpreterTest final : public unittest::UnitTest
    {
    public:
        explicit DavScriptInterpreterTest();

        void execute() override;

    private:
        static void testVariableAssignment();
    };
}
