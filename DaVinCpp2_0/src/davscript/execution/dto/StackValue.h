#pragma once
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
    enum class StackValueType : int8_t
    {
        NONE,
        INT,
        BOOL,
        DOUBLE,
        STRING,
        OBJECT,
    };

    struct StackValue
    {
        explicit StackValue();
        StackValue(StackValueType type, int value);
        StackValue(StackValueType type, bool value);
        StackValue(StackValueType type, double value);
        StackValue(StackValueType type, void* value);

        StackValueType type;
        union {
            int64_t int_t;
            bool bool_t;
            double double_t;
            void* object_t;
        } data;

        bool operator==(const StackValue& value) const;
    };

    static const std::unordered_map<StackValueType, std::string> STACK_VALUE_TYPE2STRING = {
        { StackValueType::INT, T_INT },
        { StackValueType::BOOL, T_BOOL },
        { StackValueType::DOUBLE, T_FLOAT },
        { StackValueType::STRING, T_STRING },
        { StackValueType::OBJECT, T_MIXED },
    };
}
