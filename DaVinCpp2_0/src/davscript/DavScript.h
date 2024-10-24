#pragma once

#ifndef DAVSCRIPT_UNIT_TEST
#include <DaVinCppYamlHelper.h>
#else
#include <DaVinCppFileSystem.h>
#endif

namespace davincpp::davscript
{
    struct DavScript
    {
        DavScript() = default;
        explicit DavScript(std::filesystem::path scriptPath);

        void loadFile();

        std::string Content;
        std::filesystem::path Location;
        std::string Name;
    };
}

#ifndef DAVSCRIPT_UNIT_TEST
namespace YAML
{
    template<> struct convert<davincpp::davscript::DavScript>
    {
        static bool decode(const Node &node, davincpp::davscript::DavScript &rhs);
    };
}
#endif