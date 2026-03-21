#pragma once
#include <tokens/CharPosition.h>
#ifndef DAVSCRIPT_UNIT_TEST
#include <DaVinCppYamlHelper.h>
#else
#include <DaVinCppFileSystem.h>
#endif

namespace davincpp::davscript
{
    class DavScript
    {
    public:
        DavScript() = default;
        explicit DavScript(std::filesystem::path scriptPath);

        void loadFile();
        void unloadFile();

        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] char getCharByPosition(CharPosition position) const;
        [[nodiscard]] bool atEndOfLine(CharPosition position) const;
        [[nodiscard]] bool atEndOfFile(CharPosition position) const;
        [[nodiscard]] size_t getLineLength(CharPosition position) const;
        [[nodiscard]] std::string_view getCodeLineByPosition(CharPosition position) const;

        [[nodiscard]] std::filesystem::path getLocation() const;
        [[nodiscard]] std::string getName() const;

    private:
        std::string m_FileContent;
        std::vector<uint32_t> m_LineCharacterOffsets;

        std::filesystem::path m_Location;
        std::string m_Name;
    };
}

#ifndef DAVSCRIPT_UNIT_TEST
namespace YAML
{
    template<> struct convert<davincpp::davscript::DavScript>
    {
        static bool decode(const Node &node, davincpp::davscript::DavScript &rhs);
    };
}
#endif