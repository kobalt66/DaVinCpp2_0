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
        Value expectedIntValue(1L);
        Value expectedBoolValue(false);
        Value expectedFloatValue(0.123);
        Value expectedStringValue(std::string("Hello World!"));

        std::filesystem::path projectPath = "../Tests/DavScriptCodeExecution/TestFiles/VariableAssignment";
        DavScript davScript("../Tests/DavScriptCodeExecution/TestFiles/VariableAssignment/Assignment.dav");

        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(davScript, lexer.getTokens());
        parser.mapScriptsToModules(projectPath);
        parser.generateAst();

        DavScriptCompiler compiler(parser.getAst(), parser.getUsedNamespaces(), projectPath);
        compiler.compile();
        compiler.saveByteCode();

        DavScriptVirtualMachine vm(projectPath);
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
        std::string expectedOutput = Console::cleanseText(Console::fmtTxt(Console::fmtLog("Hello World!"), Console::fmtLog("<int> 1")));

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

    void DavScriptCodeExecutionTest::testUsingVariable()
    {
        Value expectedIntValue(1L);

        DavScript davScript("../Tests/DavScriptCodeExecution/TestFiles/UsingVariable.dav");
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

        Value actualIntStackValue = vm.readMemory(0);
        assertTrue(expectedIntValue == actualIntStackValue);

        std::string expectedOutput = Console::cleanseText(Console::fmtLog("<int> 1"));
        assertEquals(expectedOutput, output);
    }
}
