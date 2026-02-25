#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace davincpp::davscript
{
    class ByteCastHelper final
    {
    public:
        template<typename T> static std::vector<uint8_t> nativeToBytes(const T& value);
        static std::vector<uint8_t> stringToBytes(const std::string& str);

        static uint32_t bytesToUint32(const uint8_t* bytePtr);
        static int64_t bytesToInt(const uint8_t* bytePtr);
        static bool bytesToBool(const uint8_t* bytePtr);
        static double bytesToFloat(const uint8_t* bytePtr);
        static std::string bytesToString(const uint8_t* bytePtr);
    };
}
