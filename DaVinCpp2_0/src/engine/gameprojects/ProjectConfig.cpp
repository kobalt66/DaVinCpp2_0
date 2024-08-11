#include "ProjectConfig.h"
#include <DaVinCppConstants.h>
#include <Console.h>

namespace YAML
{
    bool convert<glm::uvec2>::decode(const Node &node, glm::uvec2 &rhs)
    {
        if(!node.IsSequence() || node.size() != 2) {
            return false;
        }

        rhs.x = node[0].as<uint32_t>();
        rhs.y = node[1].as<uint32_t>();
        return true;
    }


    bool convert<davincpp::ProjectConfig>::decode(const Node &node, davincpp::ProjectConfig &rhs)
    {
        rhs.DaVinCppVersion = davincpp::DaVinCppYamlHelper::getValue<std::string>(node, "davincppVersion");
        rhs.ProjectName = davincpp::DaVinCppYamlHelper::getValue<std::string>(node, "name");

        rhs.PixelSize = davincpp::DaVinCppYamlHelper::getValue(node, "pixelSize", glm::uvec2(davincpp::DEFAULT_PIXEL_SIZEX, davincpp::DEFAULT_PIXEL_SIZEY));
        rhs.ScreenResolution = davincpp::DaVinCppYamlHelper::getValue(node, "resolution", glm::uvec2(davincpp::DEFAULT_RESOLUTION_WIDTH, davincpp::DEFAULT_RESOLUTION_HEIGHT));

        rhs.ScriptFiles = davincpp::DaVinCppYamlHelper::getSequence<davincpp::davscript::DavScript>(node, "scripts");
        rhs.TextureFiles = davincpp::DaVinCppYamlHelper::getSequence<std::filesystem::path>(node, "textures");

        rhs.Vsync = davincpp::DaVinCppYamlHelper::getValue(node, "vsync", rhs.Vsync);
        rhs.ShowCursor = davincpp::DaVinCppYamlHelper::getValue(node, "showCursor", rhs.ShowCursor);
        rhs.FlipTexturesH = davincpp::DaVinCppYamlHelper::getValue(node, "flipTexturesH", rhs.FlipTexturesH);
        rhs.DebugMode = davincpp::DaVinCppYamlHelper::getValue(node, "debugMode", rhs.DebugMode);

        return true;
    }
}
