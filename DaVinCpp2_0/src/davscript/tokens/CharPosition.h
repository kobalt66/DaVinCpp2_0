#pragma once
#include <stddef.h>

namespace davincpp::davscript {
class CharPosition final {
  public:
    CharPosition() = default;
    CharPosition(int charIdx, int line);

    void reset();

    void incrementCharIdx(int n = 1);
    void resetCharIdx();
    void incrementLine(int n = 1);
    void resetLine();

    [[nodiscard]] int getCharIdx() const;
    [[nodiscard]] int getLine() const;

  private:
    int m_CharIdx = 0;
    int m_Line    = 0;
};
} // namespace davincpp::davscript