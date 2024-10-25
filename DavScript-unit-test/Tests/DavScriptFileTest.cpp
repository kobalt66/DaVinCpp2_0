#include "DavScriptFileTest.h"

#include <DaVinCppTypes.h>
#include <DavScript.h>
#include <thread>

namespace davscript
{
    DavScriptFileTest::DavScriptFileTest()
        : UnitTest("DavScript script file loading test")
    { }


    void DavScriptFileTest::execute()
    {
        davincpp::davscript::DavScript davScript("../test.dav");
        davScript.loadFile();

        assertTrue(davScript.Content.empty() == false);
    }
}
