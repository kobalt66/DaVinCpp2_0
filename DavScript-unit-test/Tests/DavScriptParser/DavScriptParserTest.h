#pragma once

#include <UnitTest.h>

namespace davincpp::davscript
{
    class DavScriptParserTest : public unittest::UnitTest
    {
    public:
        explicit DavScriptParserTest();

        void execute() override;

    private:
        static void testAssignmentNodeSuccess();
        static void testAssignmentNodeFailure();
        static void testFunctionCallNodeSuccess();
    };
}
