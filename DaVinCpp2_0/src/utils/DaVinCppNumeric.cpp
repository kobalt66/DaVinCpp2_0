#include "DaVinCppNumeric.h"
#include <stdexcept>

namespace davincpp
{
    int DaVinCppNumeric::convertStringToInteger(std::string_view input, int _default)
    {
        try {
            return std::stoi(input.data());
        }
        catch (std::invalid_argument& error) {
            return _default;
        }
    }
}
