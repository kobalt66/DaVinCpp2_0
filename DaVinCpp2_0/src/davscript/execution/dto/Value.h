#pragma once
#include <memory>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
    enum class ValueType : int8_t
    {
        NONE,
        INT,
        BOOL,
        DOUBLE,
        STRING,
        OBJECT,
    };

    struct Value
    {
        explicit Value();
        Value(ValueType type, int value);
        Value(ValueType type, bool value);
        Value(ValueType type, double value);
        Value(ValueType type, const std::string& value);
        Value(ValueType type, void* value);

        ValueType type;
        union {
            int64_t int_t;
            bool bool_t;
            double double_t;
            const char* string_t;
            void* object_t;
        } data;

        bool operator==(const Value& value) const;
    };

    static const std::unordered_map<ValueType, std::string> STACK_VALUE_TYPE2STRING = {
        { ValueType::INT, T_INT },
        { ValueType::BOOL, T_BOOL },
        { ValueType::DOUBLE, T_FLOAT },
        { ValueType::STRING, T_STRING },
        { ValueType::OBJECT, T_MIXED },
    };
}
