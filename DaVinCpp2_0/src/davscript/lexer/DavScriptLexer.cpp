#include "DavScriptLexer.h"
#include <algorithm>
#include <Console.h>
#include <DaVinCppExceptions.h>
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

            // Lexing number tokens
            if (charInCharList(m_CurrentChar, NUMBER_CHARACTERS)) {
                char nextChar = peakNextChar();

                if (!charOnBlackList(nextChar, {T_MINUS, T_DOT})) {
                    lexNumberToken();
                    return;
                }
            }

            // Lexing simple tokens
            if (isSingleCharToken()) {
                lexSingleCharTokens();
                continue;
            }

            // Lexing more complex tokens
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
            lexCommentToken();
            return;
        }

        if (m_CurrentChar == T_AT) {
            lexVariableTypeToken();
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
            char nextChar = peakNextChar();

            if (charOnBlackList(nextChar, {T_EOF, T_NEWLINE})) {
                break;
            }

            comment << advanceChar();
        }

        m_Tokens.emplace_back(m_CurrentCharPosition, comment.str(), NONE, COMMENT);
    }

    void DavScriptLexer::lexVariableTypeToken()
    {
        std::ostringstream variableType;
        variableType << m_CurrentChar;

        while (true) {
            char nextChar = peakNextChar();

            if (charOnBlackList(nextChar, {T_EOF, T_SPACE}) || !charInCharList(nextChar, ALPHABET)) {
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

            if (!charInCharList(nextChar, WORD_ChARACTERS)) {
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
        throw davincpp::not_implemented(__LINE__, __FILE__);
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

    bool DavScriptLexer::charInCharList(char character, const std::string& charList)
    {
        return charList.find(character) != std::string::npos;
    }
}
