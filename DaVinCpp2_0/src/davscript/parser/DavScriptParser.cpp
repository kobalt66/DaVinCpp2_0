#include "DavScriptParser.h"
#include <algorithm>
#include <Console.h>
#include <iostream>
#include <ast/Ast.h>
#include <error/DavScriptErrorFormatter.h>
#include <parser/DavScriptAssignmentParser.h>

namespace davincpp::davscript
{
    DavScriptParser::DavScriptParser(const std::vector<Token>& tokens)
        : m_Tokens(tokens)
    { }

    void DavScriptParser::generateAst()
    {
        m_Ast = std::make_shared<Ast>();

        do {
            skipNewLines();
            Token nextToken = peakNextToken();

            if (nextToken.getTokenRole() == ENDOFFILE) {
                break;
            }

            std::shared_ptr<AstNode> node;
            switch (nextToken.getTokenRole()) {
                case VARIABLETYPE:
                    node = m_AssignmentParser.parseNode(this);
                    break;
                default:
                    break;
            }

            if (dynamic_cast<InvalidNode*>(node.get()) != nullptr) {
                skipUntilNextLine();
            }

            m_Ast->addNode(node);
        } while(true);

        checkForErrors();
    }

    std::shared_ptr<Ast> DavScriptParser::getAst() const
    {
        return m_Ast;
    }

    void DavScriptParser::skipNewLines()
    {
        while (peakNextToken().getTokenType() == NEWLINE) {
            advanceToken();
        }
    }

    void DavScriptParser::skipUntilNextLine()
    {
        CharPosition nextLinePosition = m_CurrentToken.getTokenPosition();
        nextLinePosition.Line += 1;

        if (m_CurrentToken.getDavScript().atEndOfFile(nextLinePosition)) {
            m_CurrentTokenIdx = static_cast<int>(m_Tokens.size() - 1);
            return;
        }

        TokenType nextTokenType = peakNextToken().getTokenType();
        while (nextTokenType != NEWLINE) {
            nextTokenType = advanceToken().getTokenType();
        }
    }

    Token DavScriptParser::advanceToken()
    {
        m_CurrentToken = peakNextToken();

        if (m_CurrentToken.getTokenRole() != ENDOFFILE) {
            m_CurrentTokenIdx++;
        }

        return m_CurrentToken;
    }

    void DavScriptParser::checkForErrors() const
    {
        if (m_ErrorMessages.empty()) {
            return;
        }

        std::stringstream errorOutput;
        errorOutput << std::endl;

        for (std::string_view errorMessage : m_ErrorMessages) {
            errorOutput << errorMessage.data() << std::endl;
        }

        errorOutput << std::endl;

        throw std::runtime_error(Console::fmtErr(
            "DavScript failed to be parsed!",
            errorOutput.str(),
            m_ErrorMessages.size(), " error(s) occurred during the parsing phase.")
        );
    }

    Token DavScriptParser::peakNextToken() const
    {
        return m_Tokens.at(m_CurrentTokenIdx + static_cast<int>(m_CurrentTokenIdx + 1 < m_Tokens.size()));
    }

    void DavScriptParser::logUnexpectedTokenError(const Token& actualToken, const Token& expectedToken)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateUnexpectedTokenError(actualToken, expectedToken));
    }

    void DavScriptParser::logInvalidValueTypeError(const Token& valueToken, TokenType expectedToken)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateInvalidValueTypeError(valueToken, expectedToken));
    }
}
