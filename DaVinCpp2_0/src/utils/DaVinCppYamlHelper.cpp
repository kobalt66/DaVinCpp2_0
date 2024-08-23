#include "DaVinCppYamlHelper.h"
#include <DaVinCppExceptions.h>
#include <gameprojects/Project.h>
#include <Console.h>

namespace davincpp
{
    template<class T> std::vector<T> DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName)
    {
        if (!node[nodeName]) {
            Console::err("Failed to get sequence from yaml node called '", nodeName, "': Target node doesn't exist!");
            throw system_error();
        }

        YAML::Node targetNode = node[nodeName];

        if (!targetNode.IsSequence() || targetNode.IsNull()) {
            Console::err("Failed to get sequence from yaml node called '", nodeName, "': Invalid data for sequence!");
            throw system_error();
        }

        size_t arraySize = targetNode.size();
        T* output = new T[arraySize];

        for (std::size_t i = 0; i < arraySize; i++) {
            output[i] = targetNode[i].as<T>();
        }

        return std::vector<T>(output, output + arraySize);
    }

    template<class T> T DaVinCppYamlHelper::getValue(const YAML::Node& baseNode, std::string_view nodeName)
    {
        if (!baseNode[nodeName]) {
            Console::err("Failed to load yaml value from yaml node called '", nodeName, "': Node doesn't exist!");
            throw system_error();
        }

        return baseNode[nodeName].as<T>();
    }

    template<class T> T DaVinCppYamlHelper::getValue(const YAML::Node& baseNode, std::string_view nodeName, T _default)
    {
        if (!baseNode[nodeName]) {
            return _default;
        }

        return baseNode[nodeName].as<T>();
    }


    void DaVinCppYamlHelper::writeYamlToFile(const YAML::Node& node, const std::filesystem::path& filepath)
    {
        YAML::Emitter emitter;
        emitter << node;
        DaVinCppFileSystem::writeFile(filepath, emitter.c_str());
    }



    template std::vector<int>                   DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<uint32_t>              DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<float>                 DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<std::string>           DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<bool>                  DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<Project>               DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<davscript::DavScript>  DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);
    template std::vector<std::filesystem::path> DaVinCppYamlHelper::getSequence(const YAML::Node& node, std::string_view nodeName);

    template int            DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName);
    template uint32_t       DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName);
    template float          DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName);
    template std::string    DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName);
    template bool           DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName);

    template int            DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName, int _default);
    template uint32_t       DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName, uint32_t _default);
    template float          DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName, float _default);
    template std::string    DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName, std::string _default);
    template bool           DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName, bool _default);
    template glm::uvec2     DaVinCppYamlHelper::getValue(const YAML::Node& node, std::string_view nodeName, glm::uvec2 _default);
}

namespace YAML
{
    bool convert<std::filesystem::path>::decode(const Node &node, std::filesystem::path &rhs)
    {
        rhs = node.as<std::string>();
        return true;
    }
}
