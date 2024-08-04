#pragma once
#include <gameprojects/Project.h>

namespace davincpp
{
    class ProjectManager
    {
    public:
        explicit ProjectManager(std::string_view davincppConfig);

        void loadProjectList();
        void initProject(std::string_view projectName);

        [[nodiscard]] std::string getDaVinCppVersion() const;

    private:
        std::string m_DaVinCppVersion;

        std::string m_DaVinCppConfig;
        std::vector<Project> m_Projects;
    };
}
