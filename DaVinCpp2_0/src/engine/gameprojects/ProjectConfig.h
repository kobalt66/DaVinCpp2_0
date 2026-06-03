#pragma once
#include <DaVinCppYamlHelper.h>
#include <DavScript.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace davincpp {
struct ProjectConfig {
    std::vector<std::filesystem::path> TextureFiles;
    std::vector<davscript::DavScript>  ScriptFiles;

    std::string DaVinCppVersion;
    std::string ProjectName;
    glm::uvec2  ScreenResolution = glm::uvec2(0);
    glm::uvec2  PixelSize        = glm::uvec2(0);
    bool        Vsync            = false;
    bool        ShowCursor       = false;
    bool        FlipTexturesH    = false;
    bool        DebugMode        = false;
};
} // namespace davincpp

namespace YAML {
template <> struct convert<glm::uvec2> {
    static bool decode(const Node& node, glm::uvec2& rhs);
};

template <> struct convert<davincpp::ProjectConfig> {
    static Node encode(const davincpp::ProjectConfig& rhs);
    static bool decode(const Node& node, davincpp::ProjectConfig& rhs);
};
} // namespace YAML
