#pragma once
#include <DavScript.h>
#include <string>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
class Token
{
public:
    Token() = default;
    Token(DavScript    davScript,
          CharPosition position,
          std::string  value,
          TokenType    type,
          TokenRole    role = NORMAL);

    explicit Token(TokenType type, TokenRole role = NORMAL, std::string specificValue = ANY_VALUE);

    bool operator==(const Token& other) const;

    void                      setTokenPosition(CharPosition position);
    void                      setActualValue(std::string_view value);
    void                      setTokenType(TokenType type);
    void                      setTokenRole(TokenRole role);
    [[nodiscard]] DavScript   getDavScript() const;
    [[nodiscard]] std::string getActualValue() const;
    [[nodiscard]] TokenType   getTokenType() const;
    [[nodiscard]] TokenRole   getTokenRole() const;

    [[nodiscard]] int          getTokenLength() const;
    [[nodiscard]] CharPosition getTokenPosition() const;

    [[nodiscard]] std::string toString() const;

private:
    DavScript m_DavScript;

    TokenType m_Type = NONE;
    TokenRole m_Role = INVALID;

    std::string  m_ActualValue;
    CharPosition m_Position;
};
}  // namespace davincpp::davscript
