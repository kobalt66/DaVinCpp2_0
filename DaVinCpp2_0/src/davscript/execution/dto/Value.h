#pragma once
#include <memory>
#include <tokens/TokenData.h>

namespace davincpp::davscript {
enum class ValueType : int8_t {
    NONE,
    INT,
    BOOL,
    DOUBLE,
    STRING,
    OBJECT,
};

struct Value {
    explicit Value();
    Value(int64_t value);
    Value(bool value);
    Value(double value);
    Value(const std::string& value);
    Value(void* value);
    ~Value();

    Value(const Value& other);
    Value& operator=(const Value& other);
    Value(Value&& other) noexcept;
    Value& operator=(Value&& other) noexcept;

    ValueType type;
    union {
        int64_t int_t;
        bool    bool_t;
        double  double_t;
        void*   string_t;
        void*   object_t;
    } data;

    bool operator==(const Value& value) const;
};

static const std::unordered_map<ValueType, std::string>
    STACK_VALUE_TYPE2STRING = {
        {ValueType::INT, T_INT},      {ValueType::BOOL, T_BOOL},
        {ValueType::DOUBLE, T_FLOAT}, {ValueType::STRING, T_STRING},
        {ValueType::OBJECT, T_MIXED},
};
} // namespace davincpp::davscript
