#include "DavScriptFileTest.h"
#include <DavScript.h>

namespace davincpp::davscript
{
    DavScriptFileTest::DavScriptFileTest()
        : UnitTest("DavScript script file loading test")
    { }


    void DavScriptFileTest::execute()
    {
        DavScript davScript("../Tests/DavScriptFiles/test.dav");
        davScript.loadFile();

        assertEquals(false, davScript.RawContent.empty());
    }
}
