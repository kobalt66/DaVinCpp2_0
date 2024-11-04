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
        LCURLY,         // {
        RCURLY,         // }
        NEWLINE,        // \n

        // Data tokens
        NUMBERINT,      // ... , -2, -1, 0, 1, 2, ...
        NUMBERFLOAT,    // ... , -2.21, -1.53, 0.03, 1.02, 2.2, ...
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
        NOT,            // !
        ASSOSIATE,      // >>
        EQUALSTO,       // ==
        MINUSEQ,        // -=
        PLUSEQ,         // +=
        DIVIDEEQ,       // /=
        ASTRIXEQ,       // *=
        NOTEQ,          // !=
        GREATEREQ,      // >=
        LESSEQ,         // <=

        // Special tokens
        UNKNOWN,        // ß, °, ...
    };

    enum TokenRole
    {
        INVALID,

        // Special roles
        COMMENT,            // # this is a comment
        FUNCTIONDOC,        // **This is how you add multiple lines to the description**
        IDENTIFIER,         // var [ asdf ] <--

        // Regular roles
        NORMAL,             // ., :, [, ...
        DATAVALUE,          // "asdf", 123, true, ...
        KEYWORD,            // if, else, function, ...
        VARIABLETYPE,       // @var, @const, ...
        VALUETYPE,          // int, string, bool, ...
        OPERATOR,           // +, -, *, /, ...
    };

    static const char T_COMMA                   = ',';
    static const char T_QUOTE                   = '"';
    static const char T_HASH                    = '#';
    static const char T_AT                      = '@';
    static const char T_SPACE                   = ' ';
    static const char T_DOT                     = '.';
    static const char T_COLON                   = ':';
    static const char T_LPARAN                  = '(';
    static const char T_RPARAN                  = ')';
    static const char T_LBRAKET                 = '[';
    static const char T_RBRAKET                 = ']';
    static const char T_LCURLY                  = '{';
    static const char T_RCURLY                  = '}';
    static const char T_NEWLINE                 = '\n';
    static const char T_EOF                     = '\0';

    static const std::string T_USE              = "use";
    static const std::string T_MODULE           = "module";
    static const std::string T_INTERNAL         = "internal";
    static const std::string T_PRIVATE          = "private";
    static const std::string T_PUBLIC           = "public";
    static const std::string T_FUNCTION         = "function";
    static const std::string T_END              = "end";
    static const std::string T_IF               = "if";
    static const std::string T_ELIF             = "elif";
    static const std::string T_ELSE             = "else";
    static const std::string T_WHILE            = "while";
    static const std::string T_DO               = "do";
    static const std::string T_THROW            = "throw";
    static const std::string T_TRY              = "try";
    static const std::string T_CATCH            = "catch";
    static const std::string T_FINALLY          = "finally";

    static const std::string T_REF              = "@ref";
    static const std::string T_VAR              = "@var";
    static const std::string T_CONST            = "@const";
    static const std::string T_REFCOMP          = "@refcomp";
    static const std::string T_ARRAY            = "@array";

    static const std::string T_VOID             = "void";
    static const std::string T_INT              = "int";
    static const std::string T_FLOAT            = "float";
    static const std::string T_BOOL             = "bool";
    static const std::string T_MIXED            = "mixed";
    static const std::string T_STRING           = "string";

    static const std::string T_NULL             = "null";
    static const std::string T_TRUE             = "true";
    static const std::string T_FALSE            = "false";

    static const char T_PLUS                    = '+';
    static const char T_MINUS                   = '-';
    static const char T_ASTRIX                  = '*';
    static const char T_DIVIDE                  = '/';
    static const std::string T_LESS             = "<";
    static const std::string T_GREATER          = ">";
    static const std::string T_EQUALS           = "=";
    static const std::string T_NOT              = "!";
    static const std::string T_ASSOSIATE        = ">>";
    static const std::string T_EQUALSTO         = "==";
    static const std::string T_MINUSEQ          = "+=";
    static const std::string T_PLUSEQ           = "-=";
    static const std::string T_DIVIDEEQ         = "/=";
    static const std::string T_ASTRIXEQ         = "*=";
    static const std::string T_NOTEQ            = "!=";
    static const std::string T_GREATEREQ        = ">=";
    static const std::string T_LESSEQ           = "<=";

    static const std::string ALPHABET                       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    static const std::string NUMBER_CHARACTERS              = "1234567890.-";
    static const std::string WORD_ChARACTERS                = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
    static const std::string MULTI_CHAR_TOKEN_CHARACTERS    = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890#@\"-+/*=!<>";

    static const std::unordered_map<char, TokenType> SINGLE_CHAR_TOKENS = {
        {  T_COMMA,     COMMA    },
        {  T_DOT,       DOT      },
        {  T_COLON,     COLON    },
        {  T_LPARAN,    LPARAN   },
        {  T_RPARAN,    RPARAN   },
        {  T_LBRAKET,   LBRAKET  },
        {  T_RBRAKET,   RBRAKET  },
        {  T_LCURLY,    LCURLY   },
        {  T_RCURLY,    RCURLY   },
        {  T_NEWLINE,   NEWLINE  },
    };

    static const std::unordered_map<std::string, TokenType> BUILTIN_VALUE_TOKENS = {
        { T_NULL,       NULL_ },
        { T_TRUE,       TRUE  },
        { T_FALSE,      FALSE },
    };

    static const std::unordered_map<std::string, TokenType> KEYWORD_TOKENS = {
        { T_USE,        USE      },
        { T_MODULE,     MODULE   },
        { T_INTERNAL,   INTERNAL },
        { T_PRIVATE,    PRIVATE  },
        { T_PUBLIC,     PUBLIC   },
        { T_FUNCTION,   FUNCTION },
        { T_END,        END      },
        { T_IF,         IF       },
        { T_ELIF,       ELIF     },
        { T_ELSE,       ELSE     },
        { T_WHILE,      WHILE    },
        { T_DO,         DO       },
        { T_THROW,      THROW    },
        { T_TRY,        TRY      },
        { T_CATCH,      CATCH    },
        { T_FINALLY,    FINALLY  },
    };

    static const std::unordered_map<std::string, TokenType> VARIABLE_TYPE_TOKENS = {
        { T_REF,        REF     },
        { T_VAR,        VAR     },
        { T_CONST,      CONST   },
        { T_REFCOMP,    REFCOMP },
        { T_ARRAY,      ARRAY   },
    };

    static const std::unordered_map<std::string, TokenType> VALUE_TYPE_TOKENS = {
        { T_VOID,       VOIDTYPE   },
        { T_INT,        INTTYPE    },
        { T_FLOAT,      FLOATTYPE  },
        { T_STRING,     STRINGTYPE },
        { T_BOOL,       BOOLTYPE   },
        { T_MIXED,      MIXEDTYPE  },
    };

    static const std::unordered_map<std::string, TokenType> OPERATOR_TOKENS = {
        { std::string(1, T_PLUS),   PLUS      },
        { std::string(1, T_MINUS),  MINUS     },
        { std::string(1, T_ASTRIX), ASTRIX    },
        { std::string(1, T_DIVIDE), DIVIDE    },
        { T_LESS,                       LESS      },
        { T_GREATER,                    GREATER   },
        { T_EQUALS,                     EQUALS    },
        { T_NOT,                        NOT       },
        { T_ASSOSIATE,                  ASSOSIATE },
        { T_EQUALSTO,                   EQUALSTO  },
        { T_MINUSEQ,                    MINUSEQ   },
        { T_PLUSEQ,                     PLUSEQ    },
        { T_DIVIDEEQ,                   DIVIDEEQ  },
        { T_ASTRIXEQ,                   ASTRIXEQ  },
        { T_NOTEQ,                      NOTEQ     },
        { T_GREATEREQ,                  GREATEREQ },
        { T_LESSEQ,                     LESSEQ    },
    };
}