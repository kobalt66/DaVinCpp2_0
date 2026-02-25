#include "DavScriptParserTest.h"
#include <DavScript.h>
#include <parser/ast/AssignmentNode.h>
#include <parser/ast/Ast.h>
#include <parser/ast/ValueNode.h>
#include <lexer/DavScriptLexer.h>
#include <parser/DavScriptParser.h>

namespace davincpp::davscript
{
    DavScriptParserTest::DavScriptParserTest()
        : UnitTest("Testing the functionality of the DavScript parser")
    { }

    void DavScriptParserTest::execute()
    {
        assertTestStep(testAssignmentNodeSuccess());
        assertTestStep(testAssignmentNodeFailure());
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
        DavScript davScript("../Tests/DavScriptParser/TestFiles/AssignmentFailure.dav");

        DavScriptLexer lexer(davScript);
        lexer.generateTokens();

        DavScriptParser parser(lexer.getTokens());
        parser.generateAst();
    }
}
