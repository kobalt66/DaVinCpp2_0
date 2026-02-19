#include "StackValue.h"

#include <memory>

namespace davincpp::davscript
{
    StackValue::StackValue()
        : type(StackValueType::NONE), data({})
    {
        data.int_t = 0;
        data.bool_t = false;
        data.double_t = 0.0;
        data.object_t = nullptr;
    }

    StackValue::StackValue(StackValueType type, int value)
        : type(type), data({})
    {
        data.int_t = value;
    }

    StackValue::StackValue(StackValueType type, bool value)
        : type(type), data({})
    {
        data.bool_t = value;
    }

    StackValue::StackValue(StackValueType type, double value)
        : type(type), data({})
    {
        data.double_t = value;
    }

    StackValue::StackValue(StackValueType type, void* value)
        : type(type), data({})
    {
        data.object_t = value;
    }

    bool StackValue::operator==(const StackValue& value) const
    {
        if (type != value.type) {
            return false;
        }

        switch (type) {
            case StackValueType::INT:
                return data.int_t == value.data.int_t;
            case StackValueType::BOOL:
                return data.bool_t == value.data.bool_t;
            case StackValueType::DOUBLE:
                return data.double_t == value.data.double_t;
            case StackValueType::STRING:
                if (auto str = static_cast<const char*>(data.object_t)) {
                    if (auto otherStr = static_cast<const char*>(value.data.object_t)) {
                        return std::string(str) == std::string(otherStr);
                    }
                }
                return false;
            case StackValueType::OBJECT:
            default:
                return false;
        }
    }
}
