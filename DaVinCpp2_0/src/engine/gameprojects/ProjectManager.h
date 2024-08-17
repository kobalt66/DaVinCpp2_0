#pragma once
#include <gameprojects/Project.h>

namespace davincpp
{
    class ProjectManager
    {
    public:
        explicit ProjectManager(std::string_view davincppConfig);

        void loadProjectList();
        void initProject(const Project& projectName);

        [[nodiscard]] std::string getDaVinCppVersion() const;
        [[nodiscard]] const std::vector<Project>& getProjectList() const;
        [[nodiscard]] const std::vector<std::string>& getLacacyVersions() const;

    private:
        std::string m_DaVinCppVersion;
        std::vector<std::string> m_LegacyVersions;

        std::string m_DaVinCppConfig;
        std::vector<Project> m_Projects;
    };
}
