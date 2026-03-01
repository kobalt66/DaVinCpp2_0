#include "Token.h"
#include <Console.h>

#include <utility>

namespace davincpp::davscript
{
    void CharPosition::reset()
    {
        Line = 0;
        CharIdx = -1;
    }


    Token::Token(
        DavScript davScript,
        CharPosition position,
        std::string value,
        TokenType type,
        TokenRole role
        ) : m_DavScript(std::move(davScript)),
            m_Position(position),
            m_ActualValue(std::move(value)),
            m_Type(type),
            m_Role(role)
    {
        m_DavScript.unloadFile();
    }

    Token::Token(
        TokenType type,
        TokenRole role,
        std::string specificValue
    ): m_Type(type),
        m_Role(role),
        m_ActualValue(std::move(specificValue))
    { }

    bool Token::operator==(const Token& other) const
    {
        return m_Role == other.m_Role && m_Type == other.m_Type && m_ActualValue == other.m_ActualValue;
    }

    void Token::setTokenPosition(CharPosition position)
    {
        m_Position = position;
    }

    void Token::setActualValue(std::string_view value)
    {
        m_ActualValue = value;
    }

    void Token::setTokenType(TokenType type)
    {
        m_Type = type;
    }

    void Token::setTokenRole(TokenRole role)
    {
        m_Role = role;
    }

    DavScript Token::getDavScript() const
    {
        return m_DavScript;
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
        int valueLength = static_cast<int>(m_ActualValue.size());

        if (m_Role == DATAVALUE && m_Type == STRING) {
            return valueLength + 2;
        }

        return valueLength;
    }

    CharPosition Token::getTokenPosition() const
    {
        return m_Position;
    }

    std::string Token::toString() const
    {
        std::string_view type = TOKEN_TYPE2STRING.at(m_Type);

        if (m_ActualValue == ANY_VALUE || m_ActualValue == type) {
            return Console::fmtTxt("Role: '", TOKEN_ROLE2STRING.at(m_Role), "', Type: '", TOKEN_TYPE2STRING.at(m_Type), "'");
        }

        return Console::fmtTxt("Role: '", TOKEN_ROLE2STRING.at(m_Role), "', Type: '", type, "', Value: '", m_ActualValue, "'");
    }
}
