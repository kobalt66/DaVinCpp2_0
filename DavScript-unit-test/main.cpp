#include <DaVinCppExceptions.h>
#include <DaVinCppFileSystem.h>
#include <UnitTestEnvironment.h>
#include <DavScriptFileTest.h>

int main()
{
    try {
        davincpp::unittest::UnitTestEnvironment testEnvironment;

        testEnvironment.addUnitTest(std::make_unique<davincpp::davscript::DavScriptFileTest>());

        testEnvironment.execute();
    } catch (std::runtime_error& exception) {
        throw davincpp::davincpp_error(exception.what());
    }

    return 0;
}
