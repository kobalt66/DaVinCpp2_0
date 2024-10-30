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
            tryAdvanceChar();

            if (isSingleCharToken()) {
                lexSingleCharTokens();
                continue;
            }

            lexMultiCharTokens();
        } while (true);
    }


    const std::vector<Token>& DavScriptLexer::getTokens() const
    {
        return m_Tokens;
    }


    void DavScriptLexer::lexSingleCharTokens()
    {
        if (isOperatorToken()) {
            m_Tokens.emplace_back(m_CurrentCharPosition, std::string(1, m_CurrentChar), SINGLE_CHAR_TOKENS.at(m_CurrentChar), OPERATOR);
            return;
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, std::string(1, m_CurrentChar), SINGLE_CHAR_TOKENS.at(m_CurrentChar));
    }

    void DavScriptLexer::lexMultiCharTokens()
    {
        if (m_CurrentChar == T_HASH) {
            lexComment();
            return;
        }

        if (m_CurrentChar == T_AT) {
            lexVariableType();
            return;
        }

        if (charOnInCharList(m_CurrentChar, WORD_ChARACTERS)) {
            lexWordToken();
            return;
        }
    }

    void DavScriptLexer::lexComment()
    {
        std::ostringstream comment;
        comment << m_CurrentChar;

        while (true) {
            char nextChar = peakNextChar();

            if (charOnBlackList(nextChar, {T_EOF, T_NEWLINE})) {
                break;
            }

            comment << advanceChar();
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, comment.str(), NONE, COMMENT);
    }

    void DavScriptLexer::lexVariableType()
    {
        std::ostringstream variableType;
        variableType << m_CurrentChar;

        while (true) {
            char nextChar = peakNextChar();

            if (charOnBlackList(nextChar, {T_EOF, T_SPACE}) || !charOnInCharList(nextChar, ALPHABET)) {
                break;
            }

            variableType << advanceChar();
        }

        std::string variableTypeValue = variableType.str();

        if (VARIABLE_TYPE_TOKENS.find(variableTypeValue) == VARIABLE_TYPE_TOKENS.end()) {
            throw std::runtime_error("TODO: CHANGE ERROR MESSAGE TO SPECIAL DAVSCRIPT ERROR OUTPUT! Undefined variable type was used.");
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, variableTypeValue, VARIABLE_TYPE_TOKENS.at(variableTypeValue), VARIABLETYPE);
    }

    void DavScriptLexer::lexWordToken() {
        std::ostringstream word;
        word << m_CurrentChar;

        while (true) {
            char nextChar = peakNextChar();

            if (!charOnInCharList(nextChar, WORD_ChARACTERS)) {
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
            role = VARIABLEVALUE;
            type = BUILTIN_VALUE_TOKENS.at(wordValue);
        } else {
            role = IDENTIFIER;
        }

        if (role == NORMAL) {
            throw std::runtime_error(davincpp::Console::fmtTxt("TODO: CHANGE ERROR MESSAGE TO SPECIAL DAVSCRIPT ERROR OUTPUT! Failed to identify token for word: '", wordValue, "'"));
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, wordValue, type, role);
    }


    char DavScriptLexer::advanceChar()
    {
        m_CurrentCharPosition = getNextcharPosition();

        m_CurrentChar = m_DavScript.getCharByPosition(m_CurrentCharPosition);

        return m_CurrentChar;
    }

    char DavScriptLexer::peakNextChar()
    {
        return m_DavScript.getCharByPosition(getNextcharPosition());
    }

    CharPosition DavScriptLexer::getNextcharPosition() const
    {
        CharPosition nextCharPostion = m_CurrentCharPosition;
        nextCharPostion.CharIdx += 1;

        if (m_DavScript.atEndOfLine(nextCharPostion)) {
            nextCharPostion.CharIdx = 0;
            nextCharPostion.Line += 1;
        }

        return nextCharPostion;
    }


    bool DavScriptLexer::isSingleCharToken() const
    {
        return SINGLE_CHAR_TOKENS.find(m_CurrentChar) != SINGLE_CHAR_TOKENS.end();
    }

    bool DavScriptLexer::isOperatorToken() const
    {
        return OPERATOR_TOKENS.find(std::string(1, m_CurrentChar)) != OPERATOR_TOKENS.end();
    }


    bool DavScriptLexer::charOnBlackList(char character, const std::vector<char>& blackList)
    {
        return std::find(blackList.begin(), blackList.end(), character) != blackList.end();
    }

    bool DavScriptLexer::tokenValueOnWhiteList(std::string_view tokenValue, const std::unordered_map<std::string, TokenType>& whiteList)
    {
        return whiteList.find(tokenValue.data()) != whiteList.end();
    }

    bool DavScriptLexer::charOnInCharList(char character, const std::string& charList)
    {
        return charList.find(character) != std::string::npos;
    }
}
