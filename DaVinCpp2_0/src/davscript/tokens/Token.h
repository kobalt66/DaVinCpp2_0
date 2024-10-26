#pragma once
#include <string>

namespace davincpp::davscript
{
    enum TokenType
    {
        // Normal tokens
        COMMA,              // ,
        DOT,                // .
        COLON,              // :
        QUOTE,              // "
        LPARAN,             // (
        RPARAN,             // )
        LBRAKET,            // [
        RBRAKET,            // ]

        // Keywords
        USE,
        MODULE,
        INTERNAL,
        PRIVATE,
        PUBLIC,
        FUNCTION,
        END,
        IF,
        ELIF,
        ELSE,
        WHILE,
        DO,
        THROW,
        TRY,
        CATCH,
        FINALLY,
        NULL_,

        // Variable types
        REF,
        VAR,
        CONST,
        REFCOMP,
        ARRAY,

        // Operators
        PLUS,               // +
        MINUS,              // -
        ASTRIX,             // *
        DIVIDE,             // /
        LESS,               // <
        GREATER,            // >
        EQUALS,             // =
        ASSOSIATE,          // >>
        EQUALSTO,           // ==
        NOTEQ,              // !=
        GREATEREQ,          // >=
        LESSEQ,             // <=

        // Value types
        VOID,
        INT,
        FLOAT,
        STRING,
        BOOL,
        MIXED,

        // Special tokens
        UNKNOWN,            // ß, °, ...
        EOF_,               // end of the script
    };

    enum TokenRole
    {
        NORMAL,             // ., :, [, ...
        COMMENT,            // # this is a comment
        FUNCTIONDOC,        // **This is how you add multiple lines to the description**
        IDENTIFIER,         // var [ asdf ] <--
        NUMBER,             // ... , -2.01, -1, 0, 1, 2.2, ...
        KEYWORD,            // if, else, function, ...
        VARIABLE,           // @var, @const, ...
        OPERATOR,           // +, -, *, /, ...
        TYPE,               // int, string, bool, ...
        SPECIAL             // ß, ¼, ſ, \0, ...
    };

    struct TokenSpan
    {
        int StartIdx = 0;
        int EndIdx = 0;
    };

    struct TokenPosition
    {
        int m_Line = 0;
        int m_CharIdx = 0;
    };

    class Token
    {
    public:
        explicit Token(
            TokenPosition position,
            std::string value,
            TokenType type,
            TokenRole role = SINGLECHAR
            );

        [[nodiscard]] std::string getActualValue() const;
        [[nodiscard]] TokenType getTokenType() const;
        [[nodiscard]] TokenRole getTokenRole() const;

        [[nodiscard]] int getTokenLength() const;
        [[nodiscard]] TokenSpan getTokenSpan() const;
        [[nodiscard]] TokenPosition getTokenPosition() const;

    private:
        TokenType m_Type;
        TokenRole m_Role;

        std::string m_ActualValue;
        TokenPosition m_Position;
    };
}
