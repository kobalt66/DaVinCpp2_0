#include "Token.h"

namespace davincpp::davscript
{
    Token::Token(
        TokenPosition position,
        std::string value,
        TokenType type,
        TokenRole role
        ) : m_Position(position),
            m_ActualValue(std::move(value)),
            m_Type(type),
            m_Role(role)
    { }


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
        return { m_Position.m_CharIdx, m_Position.m_CharIdx + getTokenLength() - 1 };
    }

    TokenPosition Token::getTokenPosition() const
    {
        return m_Position;
    }
}
