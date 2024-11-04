#pragma once
#include <string>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
    struct TokenSpan
    {
        int StartIdx = 0;
        int EndIdx = 0;
    };

    struct CharPosition
    {
        int Line = 0;
        int CharIdx = 0;

        void reset();
    };

    class Token
    {
    public:
        explicit Token(
            CharPosition position,
            std::string value,
            TokenType type,
            TokenRole role = NORMAL
            );

        [[nodiscard]] std::string getActualValue() const;
        [[nodiscard]] TokenType getTokenType() const;
        [[nodiscard]] TokenRole getTokenRole() const;

        [[nodiscard]] int getTokenLength() const;
        [[nodiscard]] TokenSpan getTokenSpan() const;
        [[nodiscard]] CharPosition getTokenPosition() const;

    private:
        TokenType m_Type;
        TokenRole m_Role;

        std::string m_ActualValue;
        CharPosition m_Position;
    };
}
