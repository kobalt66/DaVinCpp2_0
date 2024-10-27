#include "DavScriptLexer.h"
#include <algorithm>
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

        while (advanceChar() != EOF_) {
            if (isSingleCharToken()) {
                if (isOperatorToken()) {
                    m_Tokens.emplace_back(m_CurrentCharPosition, std::string(1, m_CurrentChar), SINGLE_CHAR_TOKENS.at(m_CurrentChar), OPERATOR);
                    continue;
                }

                m_Tokens.emplace_back(m_CurrentCharPosition, std::string(1, m_CurrentChar), SINGLE_CHAR_TOKENS.at(m_CurrentChar));
                continue;
            }
        }
    }


    const std::vector<Token>& DavScriptLexer::getTokens() const
    {
        return m_Tokens;
    }



    char DavScriptLexer::advanceChar()
    {
        m_CurrentCharPosition.CharIdx += 1;

        if (m_DavScript.atEndOfLine(m_CurrentCharPosition)) {
            m_CurrentCharPosition.CharIdx = 0;
            m_CurrentCharPosition.Line += 1;
        }

        m_CurrentChar = m_DavScript.getCharByPosition(m_CurrentCharPosition);

        return m_CurrentChar;
    }


    bool DavScriptLexer::isSingleCharToken() const
    {
        return SINGLE_CHAR_TOKENS.find(m_CurrentChar) != SINGLE_CHAR_TOKENS.end();
    }

    bool DavScriptLexer::isOperatorToken() const
    {
        return OPERATOR_TOKENS.find(std::string(1, m_CurrentChar)) != OPERATOR_TOKENS.end();
    }
}
