#include "DavScriptLexer.h"
#include <algorithm>
#include <Console.h>
#include <utility>

namespace davincpp::davscript
{
    DavScriptLexer::DavScriptLexer(DavScript davScript)
        : m_DavScript(std::move(davScript))
    {
        m_DavScript.loadFile();
    }


    void DavScriptLexer::generateTokens()
    {
        m_CurrentCharPosition.reset();

        do {
            if (peakNextChar() == T_EOF) {
                break;
            }

            advanceChar();

            if (isSingleCharToken()) {
                lexSingleCharTokens();
                continue;
            }

            if (isMultiCharToken()) {
                lexMultiCharTokens();
                continue;
            }

            if (!charOnBlackList(m_CurrentChar, {T_SPACE})) {
                m_Tokens.emplace_back(m_CurrentCharPosition, std::string(1, m_CurrentChar), UNKNOWN, INVALID);
            }
        } while (true);
    }


    const std::vector<Token>& DavScriptLexer::getTokens() const
    {
        return m_Tokens;
    }


    void DavScriptLexer::lexSingleCharTokens()
    {
        m_Tokens.emplace_back(m_CurrentCharPosition, std::string(1, m_CurrentChar), SINGLE_CHAR_TOKENS.at(m_CurrentChar));
    }

    void DavScriptLexer::lexMultiCharTokens()
    {
        if (m_CurrentChar == T_HASH) {
            lexCommentToken();
            return;
        }

        if (m_CurrentChar == T_AT) {
            lexVariableTypeToken();
            return;
        }

        if (m_CurrentChar == T_QUOTE) {
            lexStringToken();
            return;
        }

        if (tokenValueOnWhiteList(std::string(1, m_CurrentChar), OPERATOR_TOKENS)) {
            lexOperators();
            return;
        }

        if (charInCharList(m_CurrentChar, NUMBER_CHARACTERS) && m_CurrentChar != T_DOT) {
            lexNumberToken();
            return;
        }

        if (charInCharList(m_CurrentChar, ALPHABET)) {
            lexWordToken();
            return;
        }
    }

    void DavScriptLexer::lexCommentToken()
    {
        std::ostringstream comment;
        comment << m_CurrentChar;

        while (true) {
            if (charOnBlackList(peakNextChar(), {T_EOF, T_NEWLINE})) {
                break;
            }

            comment << advanceChar();
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, comment.str(), NONE, COMMENT);
    }

    void DavScriptLexer::lexFunctionDoc()
    {
        advanceChar();
        std::ostringstream string;

        while (true) {
            char nextChar = peakNextChar();
            char secondNextChar = peakNextChar(2);

            if (nextChar == T_ASTRIX && secondNextChar == T_ASTRIX) {
                advanceChar(2);
                break;
            }

            if (charOnBlackList(nextChar, {T_NEWLINE, T_EOF})) {
                m_Tokens.emplace_back(m_CurrentCharPosition, string.str(), NONE, INVALID);
                return;
            }

            advanceChar();

            string << m_CurrentChar;
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, string.str(), NONE, FUNCTIONDOC);
    }

    void DavScriptLexer::lexVariableTypeToken()
    {
        std::ostringstream variableType;
        variableType << m_CurrentChar;

        while (true) {
            if (!charInCharList(peakNextChar(), ALPHABET)) {
                break;
            }

            variableType << advanceChar();
        }

        std::string variableTypeValue = variableType.str();

        if (VARIABLE_TYPE_TOKENS.find(variableTypeValue) == VARIABLE_TYPE_TOKENS.end()) {
            m_Tokens.emplace_back(m_CurrentCharPosition, variableTypeValue, NONE, INVALID);
            return;
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, variableTypeValue, VARIABLE_TYPE_TOKENS.at(variableTypeValue), VARIABLETYPE);
    }

    void DavScriptLexer::lexWordToken()
    {
        std::ostringstream word;
        word << m_CurrentChar;

        while (true) {
            if (!charInCharList(peakNextChar(), WORD_ChARACTERS)) {
                break;
            }

            word << advanceChar();
        }

        std::string wordValue = word.str();
        TokenType type = NONE;
        TokenRole role = NORMAL;

        if (tokenValueOnWhiteList(wordValue, KEYWORD_TOKENS)) {
            role = KEYWORD;
            type = KEYWORD_TOKENS.at(wordValue);
        } else if (tokenValueOnWhiteList(wordValue, VALUE_TYPE_TOKENS)) {
            role = VALUETYPE;
            type = VALUE_TYPE_TOKENS.at(wordValue);
        } else if (tokenValueOnWhiteList(wordValue, BUILTIN_VALUE_TOKENS)) {
            role = DATAVALUE;
            type = BUILTIN_VALUE_TOKENS.at(wordValue);
        } else {
            role = IDENTIFIER;
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, wordValue, type, role);
    }

    void DavScriptLexer::lexNumberToken()
    {
        std::ostringstream numberStr;
        numberStr << m_CurrentChar;

        bool hasDecimalPoint = false;
        while (true) {
            char nextChar = peakNextChar();

            if (!charInCharList(nextChar, NUMBER_CHARACTERS)) {
                break;
            }

            if (nextChar == T_DOT) {
                if (hasDecimalPoint) {
                    break;
                }

                hasDecimalPoint = true;
            }

            numberStr << advanceChar();
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, numberStr.str(), hasDecimalPoint ? NUMBERFLOAT : NUMBERINT, DATAVALUE);
    }

    void DavScriptLexer::lexStringToken()
    {
        std::ostringstream string;

        while (true) {
            char nextChar = peakNextChar();

            if (nextChar == T_QUOTE) {
                advanceChar();
                break;
            }

            if (charOnBlackList(nextChar, {T_NEWLINE, T_EOF})) {
                m_Tokens.emplace_back(m_CurrentCharPosition, string.str(), STRING, INVALID);
                return;
            }

            advanceChar();

            string << m_CurrentChar;
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, string.str(), STRING, DATAVALUE);
    }

    void DavScriptLexer::lexOperators()
    {
        char nextChar = peakNextChar();

        if (m_CurrentChar == T_MINUS &&
            charInCharList(nextChar,  NUMBER_CHARACTERS) &&
            !charOnBlackList(nextChar, {T_MINUS, T_DOT})
        ) {
            lexNumberToken();
            return;
        }

        if (m_CurrentChar == T_ASTRIX && nextChar == T_ASTRIX) {
            lexFunctionDoc();
            return;
        }

        std::ostringstream operatorString;
        operatorString << m_CurrentChar;

        if (tokenValueOnWhiteList(std::string(1, peakNextChar()), OPERATOR_TOKENS)) {
            operatorString << advanceChar();
        }

        std::string operatorValue = operatorString.str();

        bool validOperator = OPERATOR_TOKENS.find(operatorValue) != OPERATOR_TOKENS.end();
        TokenType type = validOperator ? OPERATOR_TOKENS.at(operatorValue) : UNKNOWN;
        TokenRole role = validOperator ? OPERATOR : INVALID;

        m_Tokens.emplace_back(m_CurrentCharPosition, operatorValue, type, role);
    }


    char DavScriptLexer::advanceChar(int positionAdvanceStep)
    {
        m_CurrentCharPosition = getNextcharPosition(positionAdvanceStep);

        m_CurrentChar = m_DavScript.getCharByPosition(m_CurrentCharPosition);

        return m_CurrentChar;
    }

    char DavScriptLexer::peakNextChar(int peakAheadStep)
    {
        return m_DavScript.getCharByPosition(getNextcharPosition(peakAheadStep));
    }

    CharPosition DavScriptLexer::getNextcharPosition(int positionAdvanceStep) const
    {
        CharPosition nextCharPostion = m_CurrentCharPosition;

        for (int i = 0; i < positionAdvanceStep; i++) {
            nextCharPostion.CharIdx += 1;

            if (m_DavScript.atEndOfFile(nextCharPostion)) {
                return nextCharPostion;
            }

            if (m_DavScript.atEndOfLine(nextCharPostion)) {
                nextCharPostion.CharIdx = 0;
                nextCharPostion.Line += 1;
            }
        }

        return nextCharPostion;
    }


    bool DavScriptLexer::isSingleCharToken() const
    {
        return SINGLE_CHAR_TOKENS.find(m_CurrentChar) != SINGLE_CHAR_TOKENS.end();
    }

    bool DavScriptLexer::isMultiCharToken() const
    {
        return MULTI_CHAR_TOKEN_CHARACTERS.find(m_CurrentChar) != std::string::npos;
    }

    bool DavScriptLexer::isOperatorToken() const
    {
        return OPERATOR_TOKENS.find(std::string(1, m_CurrentChar)) != OPERATOR_TOKENS.end();
    }


    bool DavScriptLexer::charOnWhiteList(char character, const std::vector<char>& whiteList)
    {
        return std::find(whiteList.begin(), whiteList.end(), character) != whiteList.end();
    }

    bool DavScriptLexer::charOnBlackList(char character, const std::vector<char>& blackList)
    {
        return charOnWhiteList(character, blackList);
    }

    bool DavScriptLexer::tokenValueOnWhiteList(std::string_view tokenValue, const std::unordered_map<std::string, TokenType>& whiteList)
    {
        return whiteList.find(tokenValue.data()) != whiteList.end();
    }

    bool DavScriptLexer::charInCharList(char character, const std::string& charList)
    {
        return charList.find(character) != std::string::npos;
    }
}
