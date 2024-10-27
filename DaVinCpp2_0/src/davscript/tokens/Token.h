#pragma once
#include <string>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
    struct TokenSpan
    {
        uint32_t StartIdx = 0;
        uint32_t EndIdx = 0;
    };

    struct CharPosition
    {
        uint32_t Line = 0;
        uint32_t CharIdx = 0;

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
