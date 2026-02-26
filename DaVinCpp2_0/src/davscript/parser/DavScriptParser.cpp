#include "DavScriptParser.h"
#include <algorithm>
#include <Console.h>
#include <iostream>
#include <error/DavScriptErrorFormatter.h>
#include <libraries/DavScriptLibraries.h>
#include <parser/ast/UseNode.h>

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
                case IDENTIFIER:
                    node = parseIdentifier(nextToken);
                    break;
                case KEYWORD:
                    node = parseKeywords(nextToken);
                    break;
                default:
                    logUnexpectedTokenError(nextToken, Token(NONE));
                    node = std::make_shared<InvalidNode>();
                    break;
            }

            if (dynamic_cast<InvalidNode*>(node.get()) != nullptr) {
                skipUntilNextLine();
            }

            m_Ast->addNode(node);
        } while(true);

        checkForErrors();
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

    Token DavScriptParser::peakNextToken(int n) const
    {
        return m_Tokens.at(m_CurrentTokenIdx + static_cast<int>(m_CurrentTokenIdx + n < m_Tokens.size()));
    }

    void DavScriptParser::enterScriptFile()
    {
        if (!m_CurrentNamespace.registeredSymbols.empty()) {
            m_RegisteredCustomNamespaces.emplace(m_CurrentNamespaceName, m_CurrentNamespace);
            m_CurrentNamespace.registeredSymbols.clear();
            m_CurrentNamespaceName.clear();
        }

        m_UsedNamespaces.clear();
    }

    bool DavScriptParser::useNamespace(std::string_view namespaceName)
    {
        if (DAVSCRIPT_LIBRARIES.contains(namespaceName.data())) {
            DavScriptNamespace libraryNamespace = DAVSCRIPT_LIBRARIES.at(namespaceName.data());
            m_DefinedSymbols.insert(libraryNamespace.registeredSymbols.begin(), libraryNamespace.registeredSymbols.end());

            m_UsedNamespaces.emplace_back(namespaceName.data());
            return true;
        }

        if (m_RegisteredCustomNamespaces.contains(namespaceName.data())) {
            DavScriptNamespace customNamespace = m_RegisteredCustomNamespaces.at(namespaceName.data());
            m_DefinedSymbols.insert(customNamespace.registeredSymbols.begin(), customNamespace.registeredSymbols.end());

            m_UsedNamespaces.emplace_back(namespaceName.data());
            return true;
        }

        return false;
    }

    void DavScriptParser::enterScope()
    {
        m_CurrentScopeDepth++;
    }

    void DavScriptParser::exitScope()
    {
        if (m_CurrentScopeDepth == 0) {
            return;
        }

        m_CurrentScopeDepth--;

        for (auto it = m_DefinedSymbols.begin(); it != m_DefinedSymbols.end();) {
            if (it->second.first > m_CurrentScopeDepth) {
                it = m_DefinedSymbols.erase(it);
            } else {
                ++it;
            }
        }
    }

    bool DavScriptParser::registerSymbol(std::string_view symbolName, SymbolType symbolType)
    {
        if (m_DefinedSymbols.contains(symbolName.data())) {
            return false;
        }

        m_DefinedSymbols[symbolName.data()] = {m_CurrentScopeDepth, symbolType};
        return true;
    }

    bool DavScriptParser::validateSymbol(std::string_view symbolName, SymbolType symbolType) const
    {
        return  m_DefinedSymbols.contains(symbolName.data())                        &&
                m_DefinedSymbols.at(symbolName.data()).first <= m_CurrentScopeDepth &&
                m_DefinedSymbols.at(symbolName.data()).second == symbolType;
    }

    bool DavScriptParser::doesVariableAlreadyExist(const Token& variableName) const
    {
        return m_DefinedSymbols.contains(variableName.getActualValue());
    }

    void DavScriptParser::logUnexpectedTokenError(const Token& actualToken, const Token& expectedToken)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateUnexpectedTokenError(actualToken, expectedToken));
    }

    void DavScriptParser::logInvalidValueTypeError(const Token& valueToken, TokenType expectedToken)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateInvalidValueTypeError(valueToken, expectedToken));
    }

    void DavScriptParser::logInaccessibleSymbolError(const Token& symbolToken, SymbolType symbolType)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateInaccessibleSymbolError(symbolToken, symbolType));
    }

    void DavScriptParser::logNamespaceNotFoundError(const Token& useToken, std::string_view namespaceName)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateNamespaceNotFoundError(useToken, namespaceName));
    }

    void DavScriptParser::logDuplicateSymbolName(const Token& symbolToken, SymbolType symbolType)
    {
        m_ErrorMessages.push_back(DavScriptErrorFormatter::generateDuplicateSymbolName(symbolToken, symbolType));
    }

    std::shared_ptr<Ast> DavScriptParser::getAst() const
    {
        return m_Ast;
    }

    std::shared_ptr<AstNode> DavScriptParser::parseIdentifier(const Token& nextToken)
    {
        if (validateSymbol(nextToken.getActualValue(), SymbolType::FUNCTION)) {
            return m_FunctionCallParser.parseNode(this);
        }

        return std::make_shared<InvalidNode>();
    }

    std::shared_ptr<AstNode> DavScriptParser::parseKeywords(const Token& nextToken)
    {
        switch (nextToken.getTokenType()) {
            case USE:
            {
                auto node = m_UseNodeParser.parseNode(this);

                if (auto useNode = std::dynamic_pointer_cast<UseNode>(node)) {
                    if (!useNamespace(useNode->getNamespaceName())) {
                        logNamespaceNotFoundError(nextToken, useNode->getNamespaceName());
                        return std::make_shared<InvalidNode>();
                    }
                }

                return node;
            }
            default:
                return std::make_shared<InvalidNode>();
        }
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
}
