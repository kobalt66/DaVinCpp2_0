#pragma once

#include <UnitTest.h>

namespace davincpp::davscript
{
    class DavScriptParserTest : public unittest::UnitTest
    {
    public:
        explicit DavScriptParserTest();

        void onSetup() override;

    private:
        static void testAssignmentNodeSuccess();
        void testAssignmentNodeFailure();
        static void testFunctionCallNodeSuccess();
    };
}
