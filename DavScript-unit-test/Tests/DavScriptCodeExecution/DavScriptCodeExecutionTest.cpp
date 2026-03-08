#include "DavScriptCodeExecutionTest.h"
#include <DavScript.h>
#include <execution/DavScriptCompiler.h>
#include <execution/DavScriptVirtualMachine.h>
#include <lexer/DavScriptLexer.h>
#include <parser/DavScriptParser.h>

namespace davincpp::davscript
{
    DavScriptCodeExecutionTest::DavScriptCodeExecutionTest()
        : UnitTest("Testing the functionality of the DavScript compiler and vm")
    { }

    void DavScriptCodeExecutionTest::onSetup() noexcept
    {
        registerTestStep({ "compiler & vm: variable assignments", [] { testVariableAssignment(); }});
        registerTestStep({ "compiler & vm: simple print function call", [this] { testSimplePrintFunctionCall(); }});
    }

    void DavScriptCodeExecutionTest::testVariableAssignment()
    {
        Value expectedIntValue(ValueType::INT, 1L);
        Value expectedBoolValue(ValueType::BOOL, false);
        Value expectedFloatValue(ValueType::DOUBLE, 0.123);
        Value expectedStringValue(ValueType::STRING, std::string("Hello World!"));

        DavScript davScript("../Tests/DavScriptCodeExecution/TestFiles/Assignment.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(davScript, lexer.getTokens());
        parser.generateAst();

        DavScriptCompiler compiler(parser.getAst(), parser.getUsedNamespaces(), PROJECT_DIRECTORY);
        compiler.compile();
        compiler.saveByteCode();

        DavScriptVirtualMachine vm(PROJECT_DIRECTORY);
        vm.prepareVM();
        vm.execute();

        Value actualIntStackValue = vm.readMemory(0);
        Value actualBoolStackValue = vm.readMemory(1);
        Value actualFloatStackValue = vm.readMemory(2);
        Value actualStringStackValue = vm.readMemory(3);

        assertTrue(expectedIntValue == actualIntStackValue);
        assertTrue(expectedBoolValue == actualBoolStackValue);
        assertTrue(expectedFloatValue == actualFloatStackValue);
        assertTrue(expectedStringValue == actualStringStackValue);
    }

    void DavScriptCodeExecutionTest::testSimplePrintFunctionCall()
    {
        std::string expectedOutput = Console::cleanseText(Console::fmtLog("Hello World!"));

        DavScript davScript("../Tests/DavScriptCodeExecution/TestFiles/SimplePrintFunctionCall.dav");
        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(davScript, lexer.getTokens());
        parser.generateAst();

        DavScriptCompiler compiler(parser.getAst(), parser.getUsedNamespaces(), PROJECT_DIRECTORY);
        compiler.compile();
        compiler.saveByteCode();

        DavScriptVirtualMachine vm(PROJECT_DIRECTORY);
        vm.prepareVM();

        suppressConsoleOutput();
        vm.execute();
        restoreConsoleOutput();

        std::string output = readSuppressedConsoleOutput();

        assertEquals(expectedOutput, output);
    }
}
