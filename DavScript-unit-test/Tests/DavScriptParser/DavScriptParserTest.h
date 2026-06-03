#pragma once

#include <UnitTest.h>

namespace davincpp::davscript {
class DavScriptParserTest : public unittest::UnitTest {
  public:
    explicit DavScriptParserTest();

    void onSetup() noexcept override;

  private:
    static void testAssignmentNodeSuccess();
    void        testAssignmentNodeFailure();
    static void testFunctionCallNodeSuccess();
    static void testProjectParsing();
};
} // namespace davincpp::davscript
