#pragma once
#include <UnitTest.h>

namespace davscript
{
    class DavScriptFileTest : public davincpp::unittest::UnitTest
    {
    public:
        explicit DavScriptFileTest();

        void execute() override;
    };
}
