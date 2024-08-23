#include "ProjectManager.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppExceptions.h>
#include <DaVinCppYamlHelper.h>
#include <DaVinCppString.h>
#include <yaml-cpp/yaml.h>
#include <Console.h>

namespace davincpp
{
    ProjectManager::ProjectManager(std::string_view davincppConfig)
        : m_DaVinCppConfig(davincppConfig)
    { }


    void ProjectManager::loadProjectList()
    {
        std::string configFilePath = DaVinCppFileSystem::prepareFilePath(m_DaVinCppConfig.data());

        try {
            if (!DaVinCppFileSystem::exists(configFilePath)) {
                Console::err("Failed to load davincpp config file at '", configFilePath, "': The config file could not be found!");
                throw system_error();
            }

            YAML::Node davincppConfig = YAML::LoadFile(configFilePath);

            m_DaVinCppVersion = DaVinCppYamlHelper::getValue<std::string>(davincppConfig, "davincppVersion");
            m_LegacyVersions = DaVinCppYamlHelper::getSequence<std::string>(davincppConfig, "legacyVersions");
            m_Projects = DaVinCppYamlHelper::getSequence<Project>(davincppConfig, "registeredProjects");

            for (Project& project : m_Projects) {
                project.loadProjectConfig(m_DaVinCppVersion);
            }
        }
        catch (std::runtime_error& error) {
            throw davincpp_error(Console::fmtTxt("Failed to parse yaml file at '", configFilePath, "': \n", error.what()));
        }
    }

    std::filesystem::path ProjectManager::initProject(const ProjectConfig& projectConfig, std::filesystem::path projectDirectory)
    {
        std::filesystem::path projectConfigFilePath = projectDirectory.concat(Console::fmtTxt(projectConfig.ProjectName, ".yaml"));
        YAML::Node configNode = YAML::convert<ProjectConfig>::encode(projectConfig);

        DaVinCppYamlHelper::writeYamlToFile(configNode, projectConfigFilePath);

        return projectConfigFilePath;
    }


    std::string ProjectManager::getDaVinCppVersion() const
    {
        return m_DaVinCppVersion;
    }

    const std::vector<Project>& ProjectManager::getProjectList() const
    {
        return m_Projects;
    }

    const std::vector<std::string> &ProjectManager::getLacacyVersions() const
    {
        return m_LegacyVersions;
    }

}
