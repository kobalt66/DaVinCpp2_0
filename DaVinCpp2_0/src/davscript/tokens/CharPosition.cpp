#include "CharPosition.h"

namespace davincpp::davscript
{
CharPosition::CharPosition(int charIdx, int line)
: m_CharIdx(charIdx)
, m_Line(line)
{
}

void CharPosition::reset()
{
    m_CharIdx = -1;
    m_Line    = 0;
}

void CharPosition::incrementCharIdx(int n) { m_CharIdx += n; }

void CharPosition::resetCharIdx() { m_CharIdx = 0; }

void CharPosition::incrementLine(int n) { m_Line += n; }

void CharPosition::resetLine() { m_Line = 0; }

int CharPosition::getCharIdx() const { return m_CharIdx; }

int CharPosition::getLine() const { return m_Line; }
}  // namespace davincpp::davscript
