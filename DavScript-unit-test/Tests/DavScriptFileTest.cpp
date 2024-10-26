#include "DavScriptFileTest.h"
#include <DavScript.h>

namespace davincpp::davscript
{
    DavScriptFileTest::DavScriptFileTest()
        : UnitTest("DavScript script file loading test")
    { }


    void DavScriptFileTest::execute()
    {
        DavScript davScript("../test.dav");
        davScript.loadFile();

        assertTrue(davScript.Content.empty() == false);
    }
}
