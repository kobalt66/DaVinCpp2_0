#include "ProjectConfig.h"
#include <DaVinCppConstants.h>
#include <DaVinCppExceptions.h>
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
        if (!node["davincppVersion"]) {
            davincpp::Console::err("Failed to parse project config file: No DaVinCpp verions specified!");
            throw davincpp::system_error();
        }

        rhs.DaVinCppVersion = node["davincppVersion"].as<std::string>();

        if (!node["name"]) {
            davincpp::Console::err("Failed to parse project config file: No project name defined!");
            throw davincpp::system_error();
        }

        rhs.ProjectName = node["name"].as<std::string>();

        if (node["pixelSize"]) {
            rhs.PixelSize = node["pixelSize"].as<glm::uvec2>();
        }
        else {
            rhs.PixelSize = glm::uvec2(davincpp::DEFAULT_PIXEL_SIZEX, davincpp::DEFAULT_PIXEL_SIZEY);
        }

        if (node["resolution"]) {
            rhs.ScreenResolution = node["resolution"].as<glm::uvec2>();
        }
        else {
            rhs.ScreenResolution = glm::uvec2(davincpp::DEFAULT_RESOLUTION_WIDTH, davincpp::DEFAULT_RESOLUTION_HEIGHT);
        }

        if (!node["scripts"]) {
            return true;
        }

        Node scriptsList = node["scripts"];

        if (!scriptsList.IsSequence() || scriptsList.IsNull()) {
            davincpp::Console::err("Failed to parse project config file for '", rhs.ProjectName, "': Invalid data for the project scripts list!");
            throw davincpp::system_error();
        }

        for (std::size_t i = 0; i < scriptsList.size(); i++) {
            rhs.ScriptFiles.emplace_back(scriptsList[i].as<std::string>());
        }

        Node texturesList = node["textures"];

        if (!texturesList.IsSequence() || texturesList.IsNull()) {
            davincpp::Console::err("Failed to parse project config file for '", rhs.ProjectName, "': Invalid data for the project textures list!");
            throw davincpp::system_error();
        }

        for (std::size_t i = 0; i < texturesList.size(); i++) {
            rhs.TextureFiles.emplace_back(texturesList[i].as<std::string>());
        }

        if (node["vsync"]) {
            rhs.Vsync = node["vsync"].as<bool>();
        }

        if (node["showCursor"]) {
            rhs.ShowCursor = node["showCursor"].as<bool>();
        }

        if (node["flipTexturesH"]) {
            rhs.FlipTexturesH = node["flipTexturesH"].as<bool>();
        }

        if (node["debugMode"]) {
            rhs.DebugMode = node["debugMode"].as<bool>();
        }

        return true;
    }
}
