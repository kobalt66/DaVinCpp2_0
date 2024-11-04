#pragma once
#include <string>

namespace davincpp
{
    class DaVinCppNumeric
    {
    public:
        static int convertStringToInteger(std::string_view input, int _default);
    };
}
