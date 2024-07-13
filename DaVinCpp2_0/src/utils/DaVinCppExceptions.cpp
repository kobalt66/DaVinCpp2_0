#include "DaVinCppExceptions.h"
#include <Console.h>

namespace davincpp
{
    system_error::system_error() : std::runtime_error("[SYS] fatal error") { }
    
    core_error::core_error() : std::runtime_error("[CORE] fatal error") { }
    
    glfw_error::glfw_error() : std::runtime_error("[GLFW] fatal error") { }
    
    opengl_error::opengl_error() : std::runtime_error("[OpenGL] fatal error") { }
    
    event_error::event_error() : std::runtime_error("[Event] fatal error") { }

    not_implemented::not_implemented(int line, const char* file): std::runtime_error(Console::fmtTxt("(file: ", file, ", line: ", line, ") function is not implemented!").c_str()) { }

    davincpp_error::davincpp_error(std::string_view message): std::runtime_error(message.data()) { }
}
