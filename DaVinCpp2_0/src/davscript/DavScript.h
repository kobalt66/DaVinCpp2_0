#pragma once
#include <DaVinCppFileSystem.h>
#include <DaVinCppYamlHelper.h>

namespace davincpp::davscript
{
    struct DavScript
    {
        DavScript() = default;
        explicit DavScript(std::string_view scriptPath);

        std::filesystem::path Location;
        std::string Name;
    };
}

namespace YAML
{
    template<> struct convert<davincpp::davscript::DavScript>
    {
        static bool decode(const Node &node, davincpp::davscript::DavScript &rhs);
    };
}