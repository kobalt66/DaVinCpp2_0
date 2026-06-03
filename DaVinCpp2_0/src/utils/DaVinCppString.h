#pragma once
#include <DaVinCppTypes.h>
#include <regex>
#include <string>
#include <vector>

namespace davincpp {
class DaVinCppString {
  public:
    static std::vector<std::string> split(std::string_view input,
                                          char             delimiter);
    static std::string              findReplaceAll(std::string_view   input,
                                                   const std::string& find,
                                                   const std::string& replace);
    static std::string findReplaceAllByRegex(std::string_view   input,
                                             const std::regex&  regex,
                                             const std::string& replace);

    static std::string fmtTime(msc duration);
    static std::string fmtTime(sec duration);
};
} // namespace davincpp
