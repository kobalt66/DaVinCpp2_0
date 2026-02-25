#include "Value.h"
#include <cstring>
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

    Value::Value(ValueType type, int64_t value)
        : type(type), data({})
    {
        data.int_t = value;
        data.string_t = nullptr;
    }

    Value::Value(ValueType type, bool value)
        : type(type), data({})
    {
        data.bool_t = value;
        data.string_t = nullptr;
    }

    Value::Value(ValueType type, double value)
        : type(type), data({})
    {
        data.double_t = value;
        data.string_t = nullptr;
    }

    Value::Value(ValueType type, const std::string& value)
        : type(type), data({})
    {
        data.string_t = strdup(value.c_str());
    }

    Value::Value(ValueType type, void* value)
        : type(type), data({})
    {
        data.object_t = value;
        data.string_t = nullptr;
    }

    Value::~Value()
    {
        if (type == ValueType::STRING && data.string_t) {
            free(data.string_t);
        }
    }

    Value::Value(const Value& other)
        : type(other.type), data({})
    {
        if (type == ValueType::STRING && other.data.string_t) {
            data.string_t = strdup(static_cast<const char*>(other.data.string_t));
        } else {
            data = other.data;
        }
    }

    Value& Value::operator=(const Value& other)
    {
        if (this == &other) return *this;

        if (type == ValueType::STRING && data.string_t) {
            free(data.string_t);
        }

        type = other.type;
        if (type == ValueType::STRING && other.data.string_t) {
            data.string_t = strdup(static_cast<const char*>(other.data.string_t));
        } else {
            data = other.data;
        }

        return *this;
    }

    Value::Value(Value&& other) noexcept
        : type(other.type), data(other.data)
    {
        other.type = ValueType::NONE;
        other.data.string_t = nullptr;
    }

    Value& Value::operator=(Value&& other) noexcept
    {
        if (this == &other) return *this;

        if (type == ValueType::STRING && data.string_t) {
            free(data.string_t);
        }

        type = other.type;
        data = other.data;

        other.type = ValueType::NONE;
        other.data.string_t = nullptr;

        return *this;
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
                if (data.string_t && value.data.string_t) {
                    return strcmp(static_cast<const char*>(data.string_t), static_cast<const char*>(value.data.string_t)) == 0;
                }

                return data.string_t == value.data.string_t;
            case ValueType::OBJECT:
            default:
                return false;
        }
    }
}
