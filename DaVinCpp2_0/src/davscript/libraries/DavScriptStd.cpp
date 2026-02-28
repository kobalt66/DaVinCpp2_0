#include "DavScriptStd.h"

#include <Console.h>
#include <error/DavScriptErrorFormatter.h>
#include <error/DavScriptException.h>
#include <execution/DavScriptVirtualMachine.h>

namespace davincpp::davscript
{
    namespace stdlib::io
    {
        void print(DavScriptVirtualMachine* vm)
        {
            Value value = vm->popStackValue();

            if (value.type == ValueType::OBJECT) {
                throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidParameterValue("std.io.print", 0, value.type, "int, bool, float or string"));
            }

            switch (value.type) {
                case ValueType::INT:
                    Console::log("<int> ", value.data.int_t);
                    break;
                case ValueType::BOOL:
                    Console::log(value.data.bool_t ? "true" : "false");
                    break;
                case ValueType::DOUBLE:
                    Console::log("<float> ", value.data.double_t);
                    break;
                case ValueType::STRING:
                    Console::log(static_cast<const char*>(value.data.string_t));
                    break;
                default: break;
            }
        }
    }
}
