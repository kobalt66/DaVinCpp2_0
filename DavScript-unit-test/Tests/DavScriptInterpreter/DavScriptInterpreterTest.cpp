#include "DavScriptInterpreterTest.h"

#include <DavScript.h>
#include <lexer/DavScriptLexer.h>
#include <parser/DavScriptParser.h>
#include <interpreter/DavScriptInterpreter.h>

namespace davincpp::davscript
{
    DavScriptInterpreterTest::DavScriptInterpreterTest()
        : UnitTest("Testing the functionality of the DavScript interpreter/ VM")
    { }

    void DavScriptInterpreterTest::execute()
    {
        assertTestStep(testVariableAssignment());
    }

    void DavScriptInterpreterTest::testVariableAssignment()
    {
        DavScript davScript("../Tests/DavScriptParser/TestFiles/AssignmentSuccess.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();

        DavScriptInterpreter interpreter(parser.getAst());
        interpreter.run();

        StackValue expectedStackValue(StackValueType::INT, {1});

        StackValue actualStackValue = interpreter.getStack().top();

        assertTrue(expectedStackValue == actualStackValue);
    }
}
