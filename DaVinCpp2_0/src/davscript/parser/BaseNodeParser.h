#pragma once
#include <memory>
#include <ast/AstNode.h>

#include <ast/InvalidNode.h>
#include <tokens/Token.h>
#define assert(assertion) if (!(assertion)) return std::make_shared<InvalidNode>()

namespace davincpp::davscript
{
    class DavScriptParser;

    class BaseNodeParser
    {
    public:
        virtual ~BaseNodeParser() = default;

        [[nodiscard]] virtual std::shared_ptr<AstNode> parseNode(DavScriptParser* scriptParser) = 0;

    protected:
        static void skipNewLines(DavScriptParser* scriptParser);
        static Token advanceToken(DavScriptParser* scriptParser);
        [[nodiscard]] static Token peakNextToken(DavScriptParser* scriptParser);

        static bool checkToken(const Token& actualToken, const Token& expectedToken);
        static bool checkTokenRole(const Token& actualToken, const Token& expectedToken);
        static bool checkType(const Token& actualToken, const Token& expectedToken);

        static bool assertTokenValue(DavScriptParser* scriptParser, const Token& value, const Token& valueType);
        static bool assertToken(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertTokenRole(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
        static bool assertType(DavScriptParser* scriptParser, const Token& actualToken, const Token& expectedToken);
    };
}
