#include "DavScriptInterpreterTest.h"

#include <DavScript.h>
#include <lexer/DavScriptLexer.h>
#include <parser/DavScriptParser.h>
#include <execution/DavScriptCodeExecution.h>

namespace davincpp::davscript
{
    DavScriptInterpreterTest::DavScriptInterpreterTest()
        : UnitTest("Testing the functionality of the DavScript interpreter")
    { }

    void DavScriptInterpreterTest::execute()
    {
        assertTestStep(testVariableAssignment());
    }

    void DavScriptInterpreterTest::testVariableAssignment()
    {
        StackValue expectedIntValue(StackValueType::INT, 1);
        StackValue expectedBoolValue(StackValueType::BOOL, false);
        StackValue expectedFloatValue(StackValueType::DOUBLE, 0.123);
        StackValue expectedStringValue(StackValueType::STRING, (void*) "Hello World!");

        DavScript davScript("../Tests/DavScriptParser/TestFiles/AssignmentSuccess.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();

        DavScriptCodeExecution interpreter(parser.getAst());
        interpreter.run();

        StackValue actualIntStackValue = interpreter.getVM().readMemory(0);
        StackValue actualBoolStackValue = interpreter.getVM().readMemory(1);
        StackValue actualFloatStackValue = interpreter.getVM().readMemory(2);
        StackValue actualStringStackValue = interpreter.getVM().readMemory(3);

        assertTrue(expectedIntValue == actualIntStackValue);
        assertTrue(expectedBoolValue == actualBoolStackValue);
        assertTrue(expectedFloatValue == actualFloatStackValue);
        assertTrue(expectedStringValue == actualStringStackValue);
    }
}
