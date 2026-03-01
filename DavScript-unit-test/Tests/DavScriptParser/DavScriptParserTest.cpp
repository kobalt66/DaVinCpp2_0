#include "DavScriptParserTest.h"
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

    void DavScriptParserTest::onSetup() noexcept
    {
        registerTestStep("parsing assignments: success", [] { testAssignmentNodeSuccess(); });
        registerTestStep("parsing assignments: failure", [this] { testAssignmentNodeFailure(); });
        registerTestStep("parsing function call: success: ", [] { testFunctionCallNodeSuccess(); });
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

        DavScriptParser parser(davScript, lexer.getTokens());
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

        DavScriptParser parser(davScript, lexer.getTokens());
        parser.generateAst();
        Console::log("asdf");
    }

    void DavScriptParserTest::testFunctionCallNodeSuccess()
    {
        DavScript davScript("../Tests/DavScriptParser/TestFiles/FunctionCallSuccess.dav");

        auto expectedAst = std::make_shared<Ast>();
        expectedAst->addNode(std::make_shared<UseNode>(Token(davScript, CharPosition(0, 4), "std.io", NONE, IDENTIFIER)));
        expectedAst->addNode(std::make_shared<FunctionCallNode>(
            Token(davScript, CharPosition(2, 0), "std.io.print", NONE, IDENTIFIER),
            std::vector<std::shared_ptr<AstNode>>
            {
                std::make_shared<ValueNode>(Token(davScript, CharPosition(2, 6), "1", NUMBERINT, DATAVALUE))
            }
        ));

        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(davScript, lexer.getTokens());
        parser.generateAst();

        auto ast = parser.getAst();

        assertTrue(*expectedAst == *ast);
    }
}
