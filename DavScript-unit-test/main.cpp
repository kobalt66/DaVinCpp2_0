#include <DaVinCppExceptions.h>
#include <DaVinCppFileSystem.h>
#include <UnitTestEnvironment.h>
#include <DavScriptFiles/DavScriptFileTest.h>
#include <DavScriptLexer/DavScriptLexerTest.h>

int main()
{
    try {
        davincpp::unittest::UnitTestEnvironment testEnvironment;

        testEnvironment.addUnitTest(std::make_unique<davincpp::davscript::DavScriptFileTest>());
        testEnvironment.addUnitTest(std::make_unique<davincpp::davscript::DavScriptLexerTest>());

        testEnvironment.execute();
    } catch (std::exception& exception) {
        throw davincpp::davincpp_error(exception.what());
    }

    return 0;
}
