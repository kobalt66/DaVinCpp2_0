#pragma once
#include <filesystem>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace davincpp
{
    class DaVinCppYamlHelper
    {
    public:
        template<class T> static std::vector<T> getSequence(const YAML::Node& node, std::string_view nodeName);
        template<class T> static T getValue(const YAML::Node& baseNode, std::string_view nodeName);
        template<class T> static T getValue(const YAML::Node& baseNode, std::string_view nodeName, T _default);
    };
}

namespace YAML
{
    template<> struct convert<std::filesystem::path>
    {
        static bool decode(const Node& node, std::filesystem::path& rhs);
    };
}
