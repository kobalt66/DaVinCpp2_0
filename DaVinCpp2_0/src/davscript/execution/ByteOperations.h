#pragma once
#include <cstdint>

namespace davincpp::davscript
{
    constexpr uint8_t NUL           = 0x00;
    constexpr uint8_t SUB           = 0x01;
    constexpr uint8_t MUL           = 0x02;
    constexpr uint8_t DIV           = 0x03;
    constexpr uint8_t MOD           = 0x04;
    constexpr uint8_t ST_INT        = 0x05;
    constexpr uint8_t LD_INT        = 0x06;
    constexpr uint8_t MOV_INT       = 0x07;
    constexpr uint8_t ST_BOOL       = 0x08;
    constexpr uint8_t LD_BOOL       = 0x00;
    constexpr uint8_t MOV_BOOL      = 0x0A;
    constexpr uint8_t ST_FLOAT      = 0x0B;
    constexpr uint8_t LD_FLOAT      = 0x0C;
    constexpr uint8_t MOV_FLOAT     = 0x0D;
    constexpr uint8_t ST_STRING     = 0x0E;
    constexpr uint8_t LD_STRING     = 0x0F;
    constexpr uint8_t MOV_STRING    = 0x10;
    constexpr uint8_t ST_OBJECT     = 0x11;
    constexpr uint8_t LD_OBJECT     = 0x12;
    constexpr uint8_t RET           = 0x13;
    constexpr uint8_t END           = 0x14;
    constexpr uint8_t DIE           = 0x15;
    constexpr uint8_t CALL          = 0x16;
    constexpr uint8_t JMP           = 0x17;
    constexpr uint8_t LD_LIB        = 0x18;
}
