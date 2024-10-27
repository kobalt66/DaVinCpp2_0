#pragma once
#include <unordered_map>
#include <vector>

namespace davincpp::davscript
{
    enum TokenType : int
    {
        NONE            = -1,
        EOF_,           // \0


        // Normal tokens
        COMMA,          // ,
        DOT,            // .
        COLON,          // :
        LPARAN,         // (
        RPARAN,         // )
        LBRAKET,        // [
        RBRAKET,        // ]
        NEWLINE,        // \n

        // Data tokens
        NUMBER,         // ... , -2.01, -1, 0, 1, 2.2, ...
        STRING,         // "This is a string"
        NULL_,
        TRUE,
        FALSE,

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

        // Variable types
        REF,
        VAR,
        CONST,
        REFCOMP,
        ARRAY,

        // Value types
        VOID_T,
        INT_T,
        FLOAT_T,
        STRING_T,
        BOOL_T,
        MIXED_T,

        // Operators
        PLUS,           // +
        MINUS,          // -
        ASTRIX,         // *
        DIVIDE,         // /
        LESS,           // <
        GREATER,        // >
        EQUALS,         // =
        ASSOSIATE,      // >>
        EQUALSTO,       // ==
        NOTEQ,          // !=
        GREATEREQ,      // >=
        LESSEQ,         // <=

        // Special tokens
        UNKNOWN,        // ß, °, ...
    };

    enum TokenRole
    {
        // Special roles
        COMMENT,            // # this is a comment
        FUNCTIONDOC,        // **This is how you add multiple lines to the description**
        IDENTIFIER,         // var [ asdf ] <--

        // Regular roles
        NORMAL,             // ., :, [, ...
        DATA,               // "asdf", 123, -12, ...
        KEYWORD,            // if, else, function, ...
        VARIABLE,           // @var, @const, ...
        TYPE,               // int, string, bool, ...
        OPERATOR,           // +, -, *, /, ...
        SPECIAL,            // ß, ¼, ſ, \0, ...
    };

    static const std::unordered_map<char, TokenType> SINGLE_CHAR_TOKENS = {
        {  ',',     COMMA    },
        {  '.',     DOT      },
        {  ':',     COLON    },
        {  '(',     LPARAN   },
        {  ')',     RPARAN   },
        {  '[',     LBRAKET  },
        {  ']',     RBRAKET  },
        {  '\n',    NEWLINE  },
        {  '+',     PLUS     },
        {  '-',     MINUS    },
        {  '*',     ASTRIX   },
        {  '/',     DIVIDE   },
    };

    static const std::vector DATA_TOKENS = {
        NUMBER,
        STRING,
        NULL_,
        TRUE,
        FALSE,
    };

    static const std::unordered_map<std::string, TokenType> KEYWORD_TOKENS = {
        { "use",        USE      },
        { "module",     MODULE   },
        { "internal",   INTERNAL },
        { "private",    PRIVATE  },
        { "public",     PUBLIC   },
        { "function",   FUNCTION },
        { "end",        END      },
        { "if",         IF       },
        { "elif",       ELIF     },
        { "else",       ELSE     },
        { "while",      WHILE    },
        { "do",         DO       },
        { "throw",      THROW    },
        { "try",        TRY      },
        { "catch",      CATCH    },
        { "finally",    FINALLY  },
    };

    static const std::unordered_map<std::string, TokenType> VARIABLE_TYPE_TOKENS = {
        { "@ref",    REF     },
        { "@var",    VAR     },
        { "@const",  CONST   },
        { "@refcomp",REFCOMP },
        { "@array",  ARRAY   },
    };

    static const std::unordered_map<std::string, TokenType> VALUE_TYPE_TOKENS = {
        { "void",   VOID_T   },
        { "int",    INT_T    },
        { "float",  FLOAT_T  },
        { "string", STRING_T },
        { "bool",   BOOL_T   },
        { "mixed",  MIXED_T  },
    };

    static const std::unordered_map<std::string, TokenType> OPERATOR_TOKENS = {
        { "+",  PLUS      },
        { "-",  MINUS     },
        { "*",  ASTRIX    },
        { "/",  DIVIDE    },
        { "<",  LESS      },
        { ">",  GREATER   },
        { "=",  EQUALS    },
        { ">>", ASSOSIATE },
        { "==", EQUALSTO  },
        { "!=", NOTEQ     },
        { ">=", GREATEREQ },
        { "<=", LESSEQ    },
    };
}