#include "DavScriptCodeExecutionTest.h"

#include <DavScript.h>
#include <lexer/DavScriptLexer.h>
#include <parser/DavScriptParser.h>
#include <execution/DavScriptCodeExecution.h>

namespace davincpp::davscript
{
    DavScriptCodeExecutionTest::DavScriptCodeExecutionTest()
        : UnitTest("Testing the functionality of the DavScript interpreter")
    { }

    void DavScriptCodeExecutionTest::execute()
    {
        assertTestStep(testVariableAssignment());
    }

    void DavScriptCodeExecutionTest::testVariableAssignment()
    {
        StackValue expectedIntValue(StackValueType::INT, 1);
        StackValue expectedBoolValue(StackValueType::BOOL, false);
        StackValue expectedFloatValue(StackValueType::DOUBLE, 0.123);
        StackValue expectedStringValue(StackValueType::STRING, (void*) "Hello World!");

        DavScript davScript("../Tests/DavScriptCodeExecution/TestFiles/Assignment.dav");
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
