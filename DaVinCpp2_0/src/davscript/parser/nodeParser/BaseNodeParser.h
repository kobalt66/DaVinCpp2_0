#pragma once
#include <memory>
#include <parser/ast/AstNode.h>
#include <tokens/Token.h>

#include <parser/ast/InvalidNode.h>
#define assert(assertion) if (!(assertion)) return std::make_shared<InvalidNode>()

namespace davincpp::davscript
{
    class DavScriptParser;

    class BaseNodeParser
    {
    public:
        BaseNodeParser() = default;
        virtual ~BaseNodeParser() = default;

        [[nodiscard]] virtual std::shared_ptr<AstNode> parseNode(DavScriptParser* scriptParser) = 0;

    protected:
        static bool checkToken(const Token& actualToken, const Token& expectedToken);
        static bool checkTokenRole(const Token& actualToken, const Token& expectedToken);
        static bool checkTokenType(const Token& actualToken, const Token& expectedToken);

        static bool assertTokenValue(DavScriptParser* scriptParser, const Token& value, const Token& expectedValueType);
        static bool assertToken(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertNotToken(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertTokenRole(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertNotTokenRole(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertTokenType(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertNotTokenType(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertSymbolAccess(DavScriptParser* scriptParser, const Token& symbolToken, SymbolType symbolType);
        static bool assertSymbolNoAccess(DavScriptParser* scriptParser, const Token& symbolToken, SymbolType symbolType);
        static bool assertSymbolAccess(DavScriptParser* scriptParser, const Token& symbolToken, std::vector<SymbolType> symbolTypes);
        static bool assertSymbolNoAccess(DavScriptParser* scriptParser, const Token& symbolToken, std::vector<SymbolType> symbolTypes);
        static bool assertSymbolDoesntExist(DavScriptParser* scriptParser, const Token& symbolToken, SymbolType symbolType);
    };
}
