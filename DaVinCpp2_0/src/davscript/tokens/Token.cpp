#include "Token.h"

namespace davincpp::davscript
{
    void CharPosition::reset()
    {
        Line = 0;
        CharIdx = -1;
    }


    Token::Token(
        CharPosition position,
        std::string value,
        TokenType type,
        TokenRole role
        ) : m_Position(position),
            m_ActualValue(std::move(value)),
            m_Type(type),
            m_Role(role)
    {
        // Adjust the line number: Otherwise the first line would be 0 continuing with 1, 2, 3, ...
        // What we want though is to start counting from 1. That's why I have to adjust the line count.
        m_Position.Line += 1;
    }


    std::string Token::getActualValue() const
    {
        return m_ActualValue;
    }

    TokenType Token::getTokenType() const
    {
        return m_Type;
    }

    TokenRole Token::getTokenRole() const
    {
        return m_Role;
    }


    int Token::getTokenLength() const
    {
        return static_cast<int>(m_ActualValue.size());
    }

    TokenSpan Token::getTokenSpan() const
    {
        return { m_Position.CharIdx, m_Position.CharIdx + getTokenLength() - 1 };
    }

    CharPosition Token::getTokenPosition() const
    {
        return m_Position;
    }
}
