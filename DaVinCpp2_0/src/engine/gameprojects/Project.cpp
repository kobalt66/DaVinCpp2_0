#include "Project.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppExceptions.h>
#include <yaml-cpp/yaml.h>
#include <Console.h>

namespace davincpp
{
    Project::Project(std::string_view projectPath)
        : m_ProjectPath(projectPath)
    { }


    void Project::loadProjectConfig(std::string_view davincppVersion)
    {
        if (!DaVinCppFileSystem::exists(m_ProjectPath)) {
            throw davincpp_error(Console::fmtTxt("Failed to load davincpp project at '", m_ProjectPath, "': Project file couldn't be located!"));
        }

        YAML::Node configNode = YAML::LoadFile(m_ProjectPath);
        m_Config = configNode.as<ProjectConfig>();

        if (m_Config.DaVinCppVersion != davincppVersion) {
            Console::wrn("Your project called '", m_Config.ProjectName, "' runs on an older/newer version of DaVinCpp. This may cause some unexpected behaviours or might cause the game to crash unexpectedly!");
            Console::raw(Console::GRAY, "Press enter to continue...");
            Console::newline();
            Console::awaitKeyInput();
        }
    }


    const ProjectConfig& Project::getProjectConfig() const
    {
        return m_Config;
    }
}
