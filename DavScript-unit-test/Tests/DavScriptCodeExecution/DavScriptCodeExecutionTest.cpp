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
        Value expectedIntValue(ValueType::INT, 1);
        Value expectedBoolValue(ValueType::BOOL, false);
        Value expectedFloatValue(ValueType::DOUBLE, 0.123);
        Value expectedStringValue(ValueType::STRING, (void*) "Hello World!");

        DavScript davScript("../Tests/DavScriptCodeExecution/TestFiles/Assignment.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();

        DavScriptCodeExecution interpreter(parser.getAst());
        interpreter.run();

        Value actualIntStackValue = interpreter.getVM().readMemory(0);
        Value actualBoolStackValue = interpreter.getVM().readMemory(1);
        Value actualFloatStackValue = interpreter.getVM().readMemory(2);
        Value actualStringStackValue = interpreter.getVM().readMemory(3);

        assertTrue(expectedIntValue == actualIntStackValue);
        assertTrue(expectedBoolValue == actualBoolStackValue);
        assertTrue(expectedFloatValue == actualFloatStackValue);
        assertTrue(expectedStringValue == actualStringStackValue);
    }
}
