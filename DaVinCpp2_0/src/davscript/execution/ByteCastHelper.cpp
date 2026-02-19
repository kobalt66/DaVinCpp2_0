#include "ByteCastHelper.h"

namespace davincpp::davscript
{
    std::array<uint8_t, 4> ByteCastHelper::split32Bit(uint32_t value)
    {
        return {
            static_cast<uint8_t>(value >> 0),
            static_cast<uint8_t>(value >> 8),
            static_cast<uint8_t>(value >> 16),
            static_cast<uint8_t>(value >> 24),
        };
    }

    uint32_t ByteCastHelper::join32Bit(const std::array<uint8_t, 4>& bytes)
    {
        return bytes[0] << 0 | bytes[1] << 8 | bytes[2] << 16 | bytes[3] << 24;
    }
}
