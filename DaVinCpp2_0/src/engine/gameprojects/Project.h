#pragma once
#include <gameprojects/ProjectConfig.h>

namespace davincpp
{
    class Project
    {
    public:
        explicit Project(std::string_view projectPath);

        void loadProjectConfig(std::string_view davincppVersion);

        [[nodiscard]] const ProjectConfig& getProjectConfig() const;

    private:
        ProjectConfig m_Config;
        std::string m_ProjectPath;
    };
}
