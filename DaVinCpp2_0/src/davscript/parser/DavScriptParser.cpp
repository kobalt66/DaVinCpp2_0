#include "DavScriptParser.h"
#include <algorithm>
#include <Console.h>
#include <DaVinCppString.h>
#include <ranges>
#include <utility>
#include <error/DavScriptErrorFormatter.h>
#include <execution/DavScriptCompiler.h>
#include <lexer/DavScriptLexer.h>
#include <libraries/DavScriptLibraries.h>
#include <parser/ast/FunctionCallNode.h>
#include <parser/ast/IdentifierNode.h>
#include <parser/ast/UseNode.h>

namespace davincpp::davscript
{
std::unordered_map<IdentifierNode, DavScript>            DavScriptParser::ModuleScriptMap;
std::unordered_map<IdentifierNode, std::shared_ptr<Ast>> DavScriptParser::ParsedScriptFilesMap;
std::unordered_map<IdentifierNode, DavScriptNamespace> DavScriptParser::RegisteredCustomNamespaces;

DavScriptParser::DavScriptParser(DavScript scriptFile, const std::vector<Token>& tokens, bool root)
: m_CurrentScript(std::move(scriptFile))
, m_Tokens(tokens)
, m_IsRoot(root)
{
    if (m_IsRoot)
    {
        ModuleScriptMap.clear();
        ParsedScriptFilesMap.clear();
        RegisteredCustomNamespaces.clear();
    }
}

void DavScriptParser::generateAst()
{
    if (m_CurrentAst == nullptr)
    {
        m_CurrentAst = std::make_shared<Ast>();
    }

    try
    {
        do
        {
            skipNewLines();
            Token nextToken = peakNextToken();

            if (nextToken.getTokenRole() == ENDOFFILE)
            {
                break;
            }

            std::shared_ptr<AstNode> node;
            switch (nextToken.getTokenRole())
            {
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

            if (dynamic_cast<InvalidNode*>(node.get()) != nullptr)
            {
                skipUntilNextLine();
            }

            m_CurrentAst->addNode(node);
        } while (true);
    }
    catch (const std::exception& e)
    {
        m_ErrorMessages.emplace_back(e.what());
    }

    checkForErrors();
}

void DavScriptParser::mapScriptsToModules(const std::filesystem::path& projectDirectory)
{
    ModuleScriptMap.clear();
    RegisteredCustomNamespaces.clear();

    std::vector<std::filesystem::directory_entry> davLibsDirectoryContents
        = DaVinCppFileSystem::getFilesInDirectoryRecursive(
            DaVinCppFileSystem::prepareFilePath("[DAV_LIBS]"));
    std::vector<std::filesystem::directory_entry> combinedDirectoryContents
        = DaVinCppFileSystem::getFilesInDirectoryRecursive(projectDirectory);
    combinedDirectoryContents.insert(combinedDirectoryContents.end(),
                                     davLibsDirectoryContents.begin(),
                                     davLibsDirectoryContents.end());

    for (const auto& directoryEntry : combinedDirectoryContents)
    {
        if (directoryEntry.is_directory())
        {
            continue;
        }

        DavScript script(directoryEntry.path());
        script.loadFile();

        std::string codeLine = script.getCodeLineByWord(T_MODULE);

        IdentifierNode moduleIdentifier;
        if (codeLine.empty())
        {
            std::string generatedModuleName = script.getLocation();
            generatedModuleName             = DaVinCppString::findReplaceAll(
                generatedModuleName, Console::fmtTxt(projectDirectory.string(), "/"), "");
            generatedModuleName = DaVinCppString::findReplaceAll(generatedModuleName, " ", "_");
            generatedModuleName = DaVinCppString::findReplaceAll(generatedModuleName, "/", ".");
            generatedModuleName = DaVinCppString::findReplaceAll(generatedModuleName, ".dav", "");
            moduleIdentifier    = IdentifierNode(
                Token(script, CharPosition(0, 0), generatedModuleName, NONE, IDENTIFIER));
        }
        else
        {
            script.setFileContent(codeLine);

            DavScriptLexer lexer(script);
            lexer.generateTokens();

            DavScriptParser parser(script, lexer.getTokens(), false);
            parser.generateAst();

            std::vector<std::shared_ptr<IdentifierNode>> moduleNodes
                = parser.m_CurrentAst->getNodesByT<IdentifierNode>();

            if (moduleNodes.size() > 1)
            {
                throw DavScriptException(Console::fmtTxt(
                    "Multiple module nodes found in script file: ", script.getName()));
            }

            moduleIdentifier = *moduleNodes.at(0);
        }

        if (ModuleScriptMap.contains(moduleIdentifier))
        {
            logInvalidModuleNamespaceError(moduleIdentifier.getName());
            continue;
        }

        if (script == m_CurrentScript)
        {
            m_CurrentAst = std::make_shared<Ast>(moduleIdentifier);
        }

        ModuleScriptMap.emplace(moduleIdentifier, script);
    }

    checkForErrors();
}

void DavScriptParser::skipNewLines()
{
    while (peakNextToken().getTokenType() == NEWLINE)
    {
        advanceToken();
    }
}

void DavScriptParser::skipUntilNextLine()
{
    Token nextToken;

    do
    {
        nextToken = advanceToken();
    } while (nextToken.getTokenType() != NEWLINE && nextToken.getTokenRole() != ENDOFFILE);
}

Token DavScriptParser::advanceToken()
{
    m_CurrentToken = peakNextToken();

    if (m_CurrentToken.getTokenRole() != ENDOFFILE)
    {
        m_CurrentTokenIdx++;
    }

    return m_CurrentToken;
}

Token DavScriptParser::peakNextToken(int n) const
{
    return m_Tokens.at(m_CurrentTokenIdx
                       + static_cast<int>(m_CurrentTokenIdx + n < m_Tokens.size()));
}

bool DavScriptParser::useNamespace(const IdentifierNode& namespaceName)
{
    if (DAVSCRIPT_LIBRARIES.contains(namespaceName.getName().getActualValue()))
    {
        DavScriptNamespace libraryNamespace
            = DAVSCRIPT_LIBRARIES.at(namespaceName.getName().getActualValue());

        for (const auto& symbol : libraryNamespace.registeredSymbols)
        {
            m_DefinedSymbols.emplace(
                Console::fmtTxt(namespaceName.getName().getActualValue(), ".", symbol.first),
                symbol.second);
        }

        m_UsedNamespaces.emplace_back(namespaceName.getName());
        return true;
    }

    // todo: Determine the script file of the custom namespace and parse it. After that, generate a
    // namespace from the script and push it to the m_RegisteredCustomNamespaces map.

    if (RegisteredCustomNamespaces.contains(namespaceName))
    {
        DavScriptNamespace customNamespace = RegisteredCustomNamespaces.at(namespaceName);
        m_DefinedSymbols.insert(customNamespace.registeredSymbols.begin(),
                                customNamespace.registeredSymbols.end());
        m_UsedNamespaces.emplace_back(namespaceName);
        return true;
    }

    if (ModuleScriptMap.contains(namespaceName))
    {
        DavScriptNamespace customNamespace = parseUsedScriptFile(namespaceName);
        m_DefinedSymbols.insert(customNamespace.registeredSymbols.begin(),
                                customNamespace.registeredSymbols.end());
        m_UsedNamespaces.emplace_back(namespaceName);
        return true;
    }

    return false;
}

bool DavScriptParser::isUsingNamespace(std::string_view namespaceName) const
{
    return std::ranges::any_of(
        m_UsedNamespaces,
        [&namespaceName](const IdentifierNode& namespaceNameToken)
        { return namespaceNameToken.getName().getActualValue() == namespaceName; });
}

IdentifierNode DavScriptParser::getCurrentNamespaceName() const
{
    return m_CurrentAst->getModuleNamespace();
}

DavScriptNamespace DavScriptParser::getCurrentNamespace() const { return m_CurrentNamespace; }

void DavScriptParser::enterScope() { m_CurrentScopeDepth++; }

void DavScriptParser::exitScope()
{
    if (m_CurrentScopeDepth == 0)
    {
        return;
    }

    m_CurrentScopeDepth--;

    for (auto it = m_DefinedSymbols.begin(); it != m_DefinedSymbols.end();)
    {
        if (it->second->getScopeDepth() > m_CurrentScopeDepth)
        {
            it = m_DefinedSymbols.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool DavScriptParser::registerSymbol(std::string_view symbolName, SymbolType symbolType)
{
    if (m_DefinedSymbols.contains(symbolName.data()))
    {
        return false;
    }

    // todo: maybe adjust?
    m_DefinedSymbols[symbolName.data()]
        = std::make_shared<DavScriptSymbol>(m_CurrentScopeDepth, symbolType);
    m_CurrentNamespace.registeredSymbols.emplace(symbolName.data(),
                                                 m_DefinedSymbols.at(symbolName.data()));
    return true;
}

bool DavScriptParser::validateSymbol(const std::shared_ptr<IdentifierNode>& symbolName,
                                     SymbolType                             symbolType) const
{
    std::string fullName = symbolName->getName().getActualValue();

    if (isValidDefinedSymbol(fullName, symbolType))
    {
        return true;
    }

    return std::ranges::any_of(
        m_UsedNamespaces,
        [this, &symbolName, &symbolType, &fullName](const IdentifierNode& usedNamespace)
        {
            std::string namespaceSymbolName
                = Console::fmtTxt(usedNamespace.getName().getActualValue(), ".", fullName);

            if (isValidDefinedSymbol(namespaceSymbolName, symbolType))
            {
                symbolName->setName(namespaceSymbolName);
                return true;
            }

            return false;
        });
}

bool DavScriptParser::isValidDefinedSymbol(std::string_view symbolName, SymbolType symbolType) const
{
    if (!m_DefinedSymbols.contains(symbolName.data()))
    {
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
    m_ErrorMessages.push_back(
        DavScriptErrorFormatter::generateUnexpectedTokenError(actualToken, expectedToken));
}

void DavScriptParser::logInvalidValueTypeError(const Token& valueToken, TokenType expectedToken)
{
    m_ErrorMessages.push_back(
        DavScriptErrorFormatter::generateInvalidValueTypeError(valueToken, expectedToken));
}

void DavScriptParser::logInaccessibleSymbolError(const Token& symbolToken, SymbolType symbolType)
{
    m_ErrorMessages.push_back(
        DavScriptErrorFormatter::generateInaccessibleSymbolError(symbolToken, symbolType));
}

void DavScriptParser::logNamespaceNotFoundError(const Token& namespaceToken)
{
    m_ErrorMessages.push_back(
        DavScriptErrorFormatter::generateNamespaceNotFoundError(namespaceToken));
}

void DavScriptParser::logDuplicateSymbolNameError(const Token& symbolToken, SymbolType symbolType)
{
    m_ErrorMessages.push_back(
        DavScriptErrorFormatter::generateDuplicateSymbolNameError(symbolToken, symbolType));
}

void DavScriptParser::logInvalidModuleNamespaceError(const Token& moduleNameToken)
{
    m_ErrorMessages.push_back(
        DavScriptErrorFormatter::generateInvalidModuleNamespaceError(moduleNameToken));
}

std::shared_ptr<Ast> DavScriptParser::getAst() const { return m_CurrentAst; }

const std::vector<IdentifierNode>& DavScriptParser::getUsedNamespaces() const
{
    return m_UsedNamespaces;
}

void DavScriptParser::startParsingAttempt()
{
    m_ParsingAttempt = std::make_shared<DavScriptParser>(*this);
}

void DavScriptParser::commitParsingAttempt()
{
    m_ErrorMessages     = m_ParsingAttempt->m_ErrorMessages;
    m_CurrentScopeDepth = m_ParsingAttempt->m_CurrentScopeDepth;
    m_DefinedSymbols    = m_ParsingAttempt->m_DefinedSymbols;
    m_UsedNamespaces    = m_ParsingAttempt->m_UsedNamespaces;
    m_CurrentNamespace  = m_ParsingAttempt->m_CurrentNamespace;
    m_CurrentAst        = m_ParsingAttempt->m_CurrentAst;
    m_Tokens            = m_ParsingAttempt->m_Tokens;
    m_CurrentTokenIdx   = m_ParsingAttempt->m_CurrentTokenIdx;
    m_CurrentToken      = m_ParsingAttempt->m_CurrentToken;

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
    if (auto functionCallNode = std::dynamic_pointer_cast<FunctionCallNode>(node))
    {
        commitParsingAttempt();
        return functionCallNode;
    }

    rollbackParsingAttempt();
    startParsingAttempt();

    node = m_IdentifierParser.parseNode(m_ParsingAttempt.get());
    if (auto identifierNode = std::dynamic_pointer_cast<IdentifierNode>(node))
    {
        commitParsingAttempt();
        return identifierNode;
    }

    rollbackParsingAttempt();

    logUnexpectedTokenError(nextToken, Token(NONE, IDENTIFIER));
    return std::make_shared<InvalidNode>();
}

std::shared_ptr<AstNode> DavScriptParser::parseKeywords(const Token& nextToken)
{
    switch (nextToken.getTokenType())
    {
        case USE:
        {
            auto node = m_UseNodeParser.parseNode(this);

            if (auto useNode = std::dynamic_pointer_cast<UseNode>(node))
            {
                if (!useNamespace(*useNode->getNamespaceName()))
                {
                    logNamespaceNotFoundError(useNode->getNamespaceName()->getName());
                    return std::make_shared<InvalidNode>();
                }
            }

            return node;
        }
        case MODULE:
            return m_ModuleNodeParser.parseNode(this);
        default:
            return std::make_shared<InvalidNode>();
    }
}

DavScriptNamespace DavScriptParser::parseUsedScriptFile(const IdentifierNode& namespaceName)
{
    if (RegisteredCustomNamespaces.contains(namespaceName))
    {
        return RegisteredCustomNamespaces.at(namespaceName);
    }

    const DavScript& script = ModuleScriptMap.at(namespaceName);

    DavScriptLexer lexer(script);
    lexer.generateTokens();

    DavScriptParser parser(script, lexer.getTokens(), false);
    parser.generateAst();

    RegisteredCustomNamespaces[parser.getCurrentNamespaceName()] = parser.getCurrentNamespace();
    ParsedScriptFilesMap[parser.getCurrentNamespaceName()]       = parser.getAst();
    return parser.getCurrentNamespace();
}

void DavScriptParser::checkForErrors() const
{
    if (m_ErrorMessages.empty())
    {
        return;
    }

    std::stringstream errorOutput;

    if (m_IsRoot)
    {
        errorOutput << std::endl;
    }

    for (std::string_view errorMessage : m_ErrorMessages)
    {
        errorOutput << errorMessage.data() << std::endl;
    }

    errorOutput << std::endl;

    std::string errorCountStr;

    if (m_ErrorMessages.size() > 1)
    {
        errorCountStr = Console::fmtTxt(m_ErrorMessages.size(), " errors");
    }
    else if (m_ErrorMessages.size() == 1)
    {
        errorCountStr = "1 error";
    }

    if (m_IsRoot)
    {
        throw std::runtime_error(Console::fmtErr("DavScript failed to be parsed!",
                                                 errorOutput.str(),
                                                 m_CurrentScript.getName(),
                                                 ": ",
                                                 errorCountStr,
                                                 " occurred during the parsing phase."));
    }

    throw std::runtime_error(Console::fmtTxt(errorOutput.str(),
                                             m_CurrentScript.getName(),
                                             ": ",
                                             errorCountStr,
                                             " occurred during the parsing phase."));
}
}  // namespace davincpp::davscript
