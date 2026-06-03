#pragma once
#include <UnitTest.h>

namespace davincpp::davscript {
class DavScriptCodeExecutionTest final : public unittest::UnitTest {
  public:
    explicit DavScriptCodeExecutionTest();

    void onSetup() noexcept override;

  private:
    static void testVariableAssignment();
    void        testSimplePrintFunctionCall();
    void        testUsingVariable();
};
} // namespace davincpp::davscript
