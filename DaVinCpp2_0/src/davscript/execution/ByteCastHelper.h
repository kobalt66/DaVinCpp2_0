#pragma once
#include <array>
#include <cstdint>

namespace davincpp::davscript
{
    class ByteCastHelper final
    {
    public:
        static std::array<uint8_t, 4> split32Bit(uint32_t value);
        static uint32_t join32Bit(const std::array<uint8_t, 4>& bytes);
    };
}
