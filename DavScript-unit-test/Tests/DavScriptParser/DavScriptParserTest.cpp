#include "DavScriptParserTest.h"

#include <DaVinCppString.h>
#include <DavScript.h>
#include <parser/ast/AssignmentNode.h>
#include <parser/ast/Ast.h>
#include <parser/ast/ValueNode.h>
#include <lexer/DavScriptLexer.h>
#include <parser/DavScriptParser.h>
#include <parser/ast/FunctionCallNode.h>
#include <parser/ast/UseNode.h>

namespace davincpp::davscript
{
    DavScriptParserTest::DavScriptParserTest()
        : UnitTest("Testing the functionality of the DavScript parser")
    { }

    void DavScriptParserTest::execute()
    {
        assertTestStep(testAssignmentNodeSuccess());
        try { testAssignmentNodeFailure(); } catch (std::exception& exception) {
            if (!m_ExpectedException.empty()) {
                std::string actualException = DaVinCppString::findReplaceAllByRegex(exception.what(), std::regex(R"(\x1B\[[0-9;]*m|\033\[[0-9;]*m)"), "");
                if (m_ExpectedException == actualException) {
                    m_ExpectedException.clear();
                    return;
                }
                if (m_ExpectedException != exception.what()) {
                    std::string failedTestDescription = davincpp::Console::fmtTxt(
                        "\nTest step '", "testAssignmentNodeFailure()", "' failed: \n", "Expected exception was not thrown: \n",
                        "Actual exception: \n", actualException, "........................................\n",
                        "Expected exception: \n", m_ExpectedException);
                    m_ExpectedException.clear();
                    ((void) 0);
                    throw std::runtime_error(failedTestDescription);
                }
            }
            ((void) 0);
            throw std::runtime_error(davincpp::Console::fmtTxt("\nTest step '", "testAssignmentNodeFailure()", "' failed: \n",
                                                               exception.what()));
        }
        assertTestStep(testFunctionCallNodeSuccess());
    }

    void DavScriptParserTest::testAssignmentNodeSuccess()
    {
        DavScript davScript("../Tests/DavScriptParser/TestFiles/AssignmentSuccess.dav");

        auto expectedAst = std::make_shared<Ast>();
        expectedAst->addNode(std::make_shared<AssignmentNode>(
            Token(davScript, CharPosition(0, 0), T_VAR, VAR, VARIABLETYPE),
            Token(davScript, CharPosition(0, 5), "a", NONE, IDENTIFIER),
            std::make_shared<ValueTypeNode>(Token(davScript, CharPosition(0, 8), T_INT, INTTYPE, VALUETYPE)),
            std::make_shared<ValueNode>(Token(davScript, CharPosition(0, 15), "1", NUMBERINT, DATAVALUE))
        ));

        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();

        auto ast = parser.getAst();

        assertTrue(*expectedAst == *ast);
    }

    void DavScriptParserTest::testAssignmentNodeFailure()
    {
        expectException(std::filesystem::path("../Tests/DavScriptParser/TestFiles/AssignmentExpectedException.txt"));

        DavScript davScript("../Tests/DavScriptParser/TestFiles/AssignmentFailure.dav");

        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();
        Console::log("asdf");
    }

    void DavScriptParserTest::testFunctionCallNodeSuccess()
    {
        DavScript davScript("../Tests/DavScriptParser/TestFiles/FunctionCallSuccess.dav");

        auto expectedAst = std::make_shared<Ast>();
        expectedAst->addNode(std::make_shared<UseNode>("std.io"));
        expectedAst->addNode(std::make_shared<FunctionCallNode>(
            Token(davScript, CharPosition(2, 0), "print", NONE, IDENTIFIER),
            std::vector<std::shared_ptr<AstNode>>
            {
                std::make_shared<ValueNode>(Token(davScript, CharPosition(2, 6), "1", NUMBERINT, DATAVALUE))
            }
        ));

        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();

        auto ast = parser.getAst();

        assertTrue(*expectedAst == *ast);
    }
}
