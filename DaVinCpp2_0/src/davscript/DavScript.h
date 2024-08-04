#pragma once
#include <DaVinCppFileSystem.h>

namespace davincpp::davscript
{
    struct DavScript
    {
        DavScript(std::string_view scriptPath);

        std::filesystem::path Location;
        std::string Name;
    };
}
