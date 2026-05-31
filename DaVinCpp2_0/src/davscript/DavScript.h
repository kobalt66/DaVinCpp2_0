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

	bool operator==(const DavScript& other) const;

	void loadFile();
	void unloadFile();

	void setFileContent(std::string_view fileContent);

	[[nodiscard]] bool isEmpty() const;
	[[nodiscard]] char getCharByPosition(CharPosition position) const;
	[[nodiscard]] bool atEndOfLine(CharPosition position) const;
	[[nodiscard]] bool atEndOfFile(CharPosition position) const;
	[[nodiscard]] size_t getLineLength(CharPosition position) const;
	[[nodiscard]] std::string_view getCodeLineByPosition(CharPosition position) const;
	[[nodiscard]] std::string getCodeLineByWord(std::string_view word) const;

	[[nodiscard]] std::filesystem::path getLocation() const;
	[[nodiscard]] std::string getName() const;

  private:
	void computeLineOffsets();

  private:
	std::string m_FileContent;
	std::vector<uint32_t> m_LineCharacterOffsets;

	std::filesystem::path m_Location;
	std::string m_Name;
};
} // namespace davincpp::davscript

#ifndef DAVSCRIPT_UNIT_TEST
namespace YAML
{
template <>
struct convert<davincpp::davscript::DavScript>
{
	static bool decode(const Node& node, davincpp::davscript::DavScript& rhs);
};
} // namespace YAML
#endif