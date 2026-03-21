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
            Value input = vm->popStackValue();

            if (input.type == ValueType::OBJECT) {
                throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidParameterValue("std.io.print", 0, input.type, "int, bool, float or string"));
            }

            Value typeInfo = vm->tryPopStackValue();

            if (typeInfo.type != ValueType::BOOL && typeInfo.type != ValueType::NONE) {
                throw DavScriptException(DavScriptErrorFormatter::generateRuntimeErrorInvalidParameterValue("std.io.print", 1, input.type, "bool"));
            }

            switch (input.type) {
                case ValueType::INT:
                    Console::log(
                        typeInfo.data.bool_t ? "<int> " : "",
                        input.data.int_t
                    );
                    break;
                case ValueType::BOOL:
                    Console::log(
                        typeInfo.data.bool_t ? "<bool> " : "",
                        input.data.bool_t ? "true" : "false"
                    );
                    break;
                case ValueType::DOUBLE:
                    Console::log(
                        typeInfo.data.bool_t ? "<float> " : "",
                        input.data.double_t
                    );
                    break;
                case ValueType::STRING:
                    Console::log(
                        typeInfo.data.bool_t ? "<string> " : "",
                        static_cast<const char*>(input.data.string_t)
                    );
                    break;
                default: break;
            }
        }
    }
}
