#pragma once
#include <unordered_map>
#include <vector>

namespace davincpp::davscript
{
    enum TokenType : int
    {
        NONE            = -1,

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
        VOIDTYPE,
        INTTYPE,
        FLOATTYPE,
        STRINGTYPE,
        BOOLTYPE,
        MIXEDTYPE,

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
        VARIABLETYPE,       // @var, @const, ...
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
        { "void",   VOIDTYPE   },
        { "int",    INTTYPE    },
        { "float",  FLOATTYPE  },
        { "string", STRINGTYPE },
        { "bool",   BOOLTYPE   },
        { "mixed",  MIXEDTYPE  },
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


    static const char T_COMMA               = ',';
    static const char T_QUOTE               = '"';
    static const char T_HASH                = '#';
    static const char T_AT                  = '@';
    static const char T_SPACE               = ' ';
    static const char T_DOT                 = '.';
    static const char T_COLON               = ':';
    static const char T_LPARAN              = '(';
    static const char T_RPARAN              = ')';
    static const char T_LBRAKET             = '[';
    static const char T_RBRAKET             = ']';
    static const char T_NEWLINE             = '\n';
    static const char T_EOF                 = '\0';

    static const std::string T_USE          = "use";
    static const std::string T_MODULE       = "module";
    static const std::string T_INTERNAL     = "internal";
    static const std::string T_PRIVATE      = "private";
    static const std::string T_PUBLIC       = "public";
    static const std::string T_FUNCTION     = "function";
    static const std::string T_END          = "end";
    static const std::string T_IF           = "if";
    static const std::string T_ELIF         = "elif";
    static const std::string T_ELSE         = "else";
    static const std::string T_WHILE        = "while";
    static const std::string T_DO           = "do";
    static const std::string T_THROW        = "throw";
    static const std::string T_TRY          = "try";
    static const std::string T_CATCH        = "catch";
    static const std::string T_FINALLY      = "finally";

    static const std::string T_REF          = "@ref";
    static const std::string T_VAR          = "@var";
    static const std::string T_CONST        = "@const";
    static const std::string T_REFCOMP      = "@refcomp";
    static const std::string T_ARRAY        = "@array";

    static const std::string T_VOID         = "void";
    static const std::string T_INT          = "int";
    static const std::string T_FLOAT        = "float";
    static const std::string T_BOOL         = "bool";
    static const std::string T_MIXED        = "mixed";
    static const std::string T_STRING       = "string";

    static const char T_PLUS                = '+';
    static const char T_MINUS               = '-';
    static const char T_ASTRIX              = '*';
    static const char T_DIVIDE              = '/';
    static const std::string T_LESS         = "<";
    static const std::string T_GREATER      = ">";
    static const std::string T_EQUALS       = "=";
    static const std::string T_ASSOSIATE    = ">>";
    static const std::string T_EQUALSTO     = "==";
    static const std::string T_NOTEQ        = "!=";
    static const std::string T_GREATEREQ    = ">=";
    static const std::string T_LESSEQ       = "<=";

    static const std::string ALPHABET       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
}