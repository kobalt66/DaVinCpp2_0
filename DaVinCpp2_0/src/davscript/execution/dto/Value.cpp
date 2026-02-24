#include "Value.h"

#include <memory>

namespace davincpp::davscript
{
    Value::Value()
        : type(ValueType::NONE), data({})
    {
        data.int_t = 0;
        data.bool_t = false;
        data.double_t = 0.0;
        data.string_t = nullptr;
        data.object_t = nullptr;
    }

    Value::Value(ValueType type, int value)
        : type(type), data({})
    {
        data.int_t = value;
    }

    Value::Value(ValueType type, bool value)
        : type(type), data({})
    {
        data.bool_t = value;
    }

    Value::Value(ValueType type, double value)
        : type(type), data({})
    {
        data.double_t = value;
    }

    Value::Value(ValueType type, const std::string& value)
        : type(type), data({})
    {
        data.string_t = value.c_str();
    }

    Value::Value(ValueType type, void* value)
        : type(type), data({})
    {
        data.object_t = value;
    }

    bool Value::operator==(const Value& value) const
    {
        if (type != value.type) {
            return false;
        }

        switch (type) {
            case ValueType::INT:
                return data.int_t == value.data.int_t;
            case ValueType::BOOL:
                return data.bool_t == value.data.bool_t;
            case ValueType::DOUBLE:
                return data.double_t == value.data.double_t;
            case ValueType::STRING:
                return std::string(data.string_t) == std::string(value.data.string_t);
            case ValueType::OBJECT:
            default:
                return false;
        }
    }
}
