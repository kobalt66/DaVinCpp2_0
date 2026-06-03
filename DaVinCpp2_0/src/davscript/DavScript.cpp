#include "DavScript.h"

#include <DaVinCppFileSystem.h>
#include <DaVinCppString.h>
#include <tokens/TokenData.h>
#include <utility>

namespace davincpp::davscript {
DavScript::DavScript(std::filesystem::path scriptPath)
    : m_Location(std::move(scriptPath)) {
    m_Name = m_Location.filename();
}

bool DavScript::operator==(const DavScript& other) const {
    return m_Location == other.m_Location;
}

void DavScript::loadFile() {
    if (!m_FileContent.empty()) {
        return;
    }

    m_FileContent = DaVinCppFileSystem::readFile(m_Location);
    computeLineOffsets();
}

void DavScript::unloadFile() {
    m_FileContent.clear();
    m_LineCharacterOffsets.clear();
}

void DavScript::setFileContent(std::string_view fileContent) {
    m_FileContent = fileContent;
    computeLineOffsets();
}

bool DavScript::isEmpty() const {
    return m_FileContent.empty() || m_LineCharacterOffsets.empty();
}

char DavScript::getCharByPosition(CharPosition position) const {
    if (atEndOfFile(position)) {
        return T_EOF;
    }

    std::string_view line = getCodeLineByPosition(position);

    if (atEndOfLine(position)) {
        return line.at(line.size() - 1);
    }

    return line.at(position.getCharIdx());
}

bool DavScript::atEndOfLine(CharPosition position) const {
    return position.getCharIdx() >= getLineLength(position);
}

bool DavScript::atEndOfFile(CharPosition position) const {
    return position.getLine() >= m_LineCharacterOffsets.size() ||
           (position.getLine() == m_LineCharacterOffsets.size() - 1 &&
            atEndOfLine(position));
}

size_t DavScript::getLineLength(CharPosition position) const {
    size_t lineOffset = m_LineCharacterOffsets.at(position.getLine());

    size_t nextLineOffset;
    if (position.getLine() + 1 < m_LineCharacterOffsets.size()) {
        nextLineOffset = m_LineCharacterOffsets.at(position.getLine() + 1);
    } else {
        nextLineOffset = m_FileContent.size();
    }

    return nextLineOffset - lineOffset;
}

std::string_view DavScript::getCodeLineByPosition(CharPosition position) const {
    if (atEndOfFile(position)) {
        return "";
    }

    size_t startIdx = m_LineCharacterOffsets.at(position.getLine());
    return {&m_FileContent.at(startIdx), getLineLength(position)};
}

std::string DavScript::getCodeLineByWord(std::string_view word) const {
    for (size_t i = 0; i < m_LineCharacterOffsets.size(); i++) {
        std::string_view line =
            getCodeLineByPosition(CharPosition(0, static_cast<int>(i)));

        if (line.find(word) != std::string_view::npos) {
            return std::string(line);
        }
    }

    return "";
}

std::filesystem::path DavScript::getLocation() const { return m_Location; }

std::string DavScript::getName() const { return m_Name; }

void DavScript::computeLineOffsets() {
    m_LineCharacterOffsets.clear();
    m_LineCharacterOffsets.push_back(0);

    if (m_FileContent.empty()) {
        return;
    }

    for (size_t i = 0; i < m_FileContent.size(); ++i) {
        if (m_FileContent[i] == T_NEWLINE) {
            m_LineCharacterOffsets.push_back(i + 1);
        }
    }
}
} // namespace davincpp::davscript

#ifndef DAVSCRIPT_UNIT_TEST
namespace YAML {
bool convert<davincpp::davscript::DavScript>::decode(
    const Node& node, davincpp::davscript::DavScript& rhs) {
    rhs = davincpp::davscript::DavScript(node.as<std::string>());
    return true;
}

} // namespace YAML
#endif