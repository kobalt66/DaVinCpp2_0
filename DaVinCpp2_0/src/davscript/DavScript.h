#pragma once

#ifndef DAVSCRIPT_UNIT_TEST
#include <DaVinCppYamlHelper.h>
#else
#include <DaVinCppFileSystem.h>
#endif
#include <tokens/Token.h>

namespace davincpp::davscript
{
    struct DavScript
    {
        DavScript() = default;
        explicit DavScript(std::filesystem::path scriptPath);

        void loadFile();

        [[nodiscard]] char getCharByPosition(CharPosition position) const;
        [[nodiscard]] bool atEndOfLine(CharPosition position) const;
        [[nodiscard]] bool atEndOfFile(CharPosition position) const;

        std::string RawContent;
        std::vector<std::string> RefinedContent;

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