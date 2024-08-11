#pragma once
#include <gameprojects/ProjectConfig.h>
#include <yaml-cpp/yaml.h>

namespace davincpp
{
    class Project
    {
    public:
        Project() = default;
        explicit Project(std::string_view projectPath);

        void loadProjectConfig(std::string_view davincppVersion);

        [[nodiscard]] const ProjectConfig& getProjectConfig() const;

    private:
        ProjectConfig m_Config;
        std::string m_ProjectPath;
    };
}

namespace YAML
{
    template<> struct convert<davincpp::Project>
    {
        static bool decode(const Node& node, davincpp::Project& rhs);
    };
}
