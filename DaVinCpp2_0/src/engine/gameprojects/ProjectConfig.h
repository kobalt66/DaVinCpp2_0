#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>
#include <DavScript.h>

namespace davincpp
{
    struct ProjectConfig
    {
        std::vector<std::filesystem::path> TextureFiles;
        std::vector<davscript::DavScript> ScriptFiles;

        std::string DaVinCppVersion;
        std::string ProjectName;
        glm::uvec2 ScreenResolution = glm::uvec2(0);
        glm::uvec2 PixelSize = glm::uvec2(0);
    };
}

namespace YAML
{
    template<> struct convert<glm::uvec2>
    {
        static bool decode(const Node& node, glm::uvec2& rhs);
    };

    template<> struct convert<davincpp::ProjectConfig>
    {
        static bool decode(const Node& node, davincpp::ProjectConfig& rhs);
    };
}
