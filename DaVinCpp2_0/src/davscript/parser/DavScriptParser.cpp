#include "DavScriptParser.h"
#include <algorithm>
#include <Console.h>
#include <iostream>
#include <ranges>
#include <utility>
#include <error/DavScriptErrorFormatter.h>
#include <execution/DavScriptCompiler.h>
#include <libraries/DavScriptLibraries.h>
#include <parser/ast/FunctionCallNode.h>
#include <parser/ast/IdentifierNode.h>
#include <parser/ast/UseNode.h>

namespace davincpp::davscript
{
    DavScriptParser::DavScriptParser(DavScript scriptFile, const std::vector<Token>& tokens)
        : m_CurrentScriptFile(std::move(scriptFile)), m_Tokens(tokens)
    { }

    void DavScriptParser::generateAst()
    {
        m_Ast = std::make_shared<Ast>();

        try {
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
        } catch (const std::exception& e) {
            m_ErrorMessages.emplace_back(e.what());
        }

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
        Token nextToken;

        do {
            nextToken = advanceToken();
        } while (nextToken.getTokenType() != NEWLINE && nextToken.getTokenRole() != ENDOFFILE);
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

    bool DavScriptParser::useNamespace(const Token& namespaceName)
    {
        if (DAVSCRIPT_LIBRARIES.contains(namespaceName.getActualValue())) {
            DavScriptNamespace libraryNamespace = DAVSCRIPT_LIBRARIES.at(namespaceName.getActualValue());

            for (const auto& symbol : libraryNamespace.registeredSymbols) {
                m_DefinedSymbols.emplace(Console::fmtTxt(namespaceName.getActualValue(), ".", symbol.first), symbol.second);
            }

            m_UsedNamespaces.emplace_back(namespaceName);
            return true;
        }

        // todo: Determine the script file of the custom namespace and parse it. After that, generate a namespace from the script and push it to the m_RegisteredCustomNamespaces map.

        if (m_RegisteredCustomNamespaces.contains(namespaceName.getActualValue())) {
            DavScriptNamespace customNamespace = m_RegisteredCustomNamespaces.at(namespaceName.getActualValue());
            m_DefinedSymbols.insert(customNamespace.registeredSymbols.begin(), customNamespace.registeredSymbols.end());

            m_UsedNamespaces.emplace_back(namespaceName);
            return true;
        }

        return false;
    }

    bool DavScriptParser::isUsingNamespace(std::string_view namespaceName) const
    {
        return std::ranges::any_of(m_UsedNamespaces, [&namespaceName](const Token& namespaceNameToken)
        {
            return namespaceNameToken.getActualValue() == namespaceName;
        });
    }

    Token DavScriptParser::getCurrentNamespaceName() const
    {
        // todo: determine the correct namespace name via the "module" keyword. Though, the fallback namespace should still be the script's name.
        return {m_CurrentScriptFile, CharPosition(0, 0), m_CurrentScriptFile.Name, NONE, IDENTIFIER};
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
            if (it->second->getScopeDepth() > m_CurrentScopeDepth) {
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

        // todo: maybe adjust?
        m_DefinedSymbols[symbolName.data()] = std::make_shared<DavScriptSymbol>(m_CurrentScopeDepth, symbolType);
        return true;
    }

    bool DavScriptParser::validateSymbol(const std::shared_ptr<IdentifierNode>& symbolName, SymbolType symbolType) const
    {
        std::string fullName = symbolName->getName().getActualValue();

        if (isValidDefinedSymbol(fullName, symbolType)) {
            return true;
        }

        return std::ranges::any_of(m_UsedNamespaces, [this, &symbolName, &symbolType, &fullName](const Token& usedNamespace)
        {
            std::string namespaceSymbolName = Console::fmtTxt(usedNamespace.getActualValue(), ".", fullName);

            if (isValidDefinedSymbol(namespaceSymbolName, symbolType)) {
                symbolName->setName(namespaceSymbolName);
                return true;
            }

            return false;
        });
    }

    bool DavScriptParser::isValidDefinedSymbol(std::string_view symbolName, SymbolType symbolType) const
    {
        if (!m_DefinedSymbols.contains(symbolName.data())) {
            return false;
        }

        std::shared_ptr<DavScriptSymbol> symbol = m_DefinedSymbols.at(symbolName.data());
        return symbol->getScopeDepth() <= m_CurrentScopeDepth && symbol->getSymbolType() == symbolType;
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

    const std::vector<Token>& DavScriptParser::getUsedNamespaces() const
    {
        return m_UsedNamespaces;
    }

    void DavScriptParser::startParsingAttempt()
    {
        m_ParsingAttempt = std::make_shared<DavScriptParser>(*this);
    }

    void DavScriptParser::commitParsingAttempt()
    {
        m_ErrorMessages = m_ParsingAttempt->m_ErrorMessages;
        m_CurrentScopeDepth = m_ParsingAttempt->m_CurrentScopeDepth;
        m_DefinedSymbols = m_ParsingAttempt->m_DefinedSymbols;
        m_RegisteredCustomNamespaces = m_ParsingAttempt->m_RegisteredCustomNamespaces;
        m_UsedNamespaces = m_ParsingAttempt->m_UsedNamespaces;
        m_CurrentNamespace = m_ParsingAttempt->m_CurrentNamespace;
        m_CurrentNamespaceName = m_ParsingAttempt->m_CurrentNamespaceName;
        m_Ast = m_ParsingAttempt->m_Ast;
        m_Tokens = m_ParsingAttempt->m_Tokens;
        m_CurrentTokenIdx = m_ParsingAttempt->m_CurrentTokenIdx;
        m_CurrentToken = m_ParsingAttempt->m_CurrentToken;

        m_ParsingAttempt.reset();
        m_ParsingAttempt = nullptr;
    }

    void DavScriptParser::rollbackParsingAttempt()
    {
        m_ParsingAttempt.reset();
        m_ParsingAttempt = nullptr;
    }

    std::shared_ptr<AstNode> DavScriptParser::parseIdentifier(const Token& nextToken)
    {
        std::shared_ptr<AstNode> node = nullptr;

        startParsingAttempt();

        node = m_FunctionCallParser.parseNode(m_ParsingAttempt.get());
        if (auto functionCallNode = std::dynamic_pointer_cast<FunctionCallNode>(node)) {
            commitParsingAttempt();
            return functionCallNode;
        }

        rollbackParsingAttempt();
        startParsingAttempt();

        node = m_IdentifierParser.parseNode(m_ParsingAttempt.get());
        if (auto identifierNode = std::dynamic_pointer_cast<IdentifierNode>(node)) {
            commitParsingAttempt();
            return identifierNode;
        }

        rollbackParsingAttempt();

        logUnexpectedTokenError(nextToken, Token(NONE, IDENTIFIER));
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
                        logNamespaceNotFoundError(nextToken, useNode->getNamespaceName().getActualValue());
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
