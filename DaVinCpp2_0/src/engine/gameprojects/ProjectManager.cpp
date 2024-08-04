#include "ProjectManager.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppExceptions.h>
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

        if (!DaVinCppFileSystem::exists(configFilePath)) {
            Console::err("Failed to load davincpp config file at '", configFilePath, "': The config file could not be found!");
            throw system_error();
        }

        YAML::Node davincppConfig = YAML::LoadFile(configFilePath);

        m_DaVinCppVersion = davincppConfig["davincppVersion"].as<std::string>();

        YAML::Node registeredProjectNode = davincppConfig["registered_projects"];

        if (!registeredProjectNode.IsSequence() || registeredProjectNode.IsNull()) {
            return;
        }

        for (std::size_t i = 0; i < registeredProjectNode.size(); i++) {
            m_Projects.emplace_back(registeredProjectNode[i].as<std::string>());
        }

        for (Project& project : m_Projects) {
            project.loadProjectConfig(m_DaVinCppVersion);
        }
    }

    void ProjectManager::initProject(std::string_view projectName)
    {

    }


    std::string ProjectManager::getDaVinCppVersion() const
    {
        return m_DaVinCppVersion.data();
    }
}
