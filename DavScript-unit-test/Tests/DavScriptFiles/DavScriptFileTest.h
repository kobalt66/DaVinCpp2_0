#pragma once
#include <UnitTest.h>

namespace davincpp::davscript
{
class DavScriptFileTest : public unittest::UnitTest
{
public:
    explicit DavScriptFileTest();

    void onSetup() noexcept override;
};
}
