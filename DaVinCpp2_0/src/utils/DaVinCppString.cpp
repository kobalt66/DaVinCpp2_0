#include "DaVinCppString.h"
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>

namespace davincpp
{
std::vector<std::string> DaVinCppString::split(std::string_view input, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream       ss(input.data());

    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::string DaVinCppString::findReplaceAll(std::string_view   input,
                                           const std::string& find,
                                           const std::string& replace)
{
    std::string str(input);

    size_t pos = str.find(find, size_t{});
    while (pos != std::string::npos)
    {
        str.replace(pos, find.length(), replace);
        pos = str.find(find, pos + replace.length());
    }

    return str;
}

std::string DaVinCppString::findReplaceAllByRegex(std::string_view   input,
                                                  const std::regex&  regex,
                                                  const std::string& replace)
{
    std::string str(input);

    std::smatch match;

    while (std::regex_search(str, match, regex))
    {
        size_t matchStartPos = match.position(0);
        str.replace(matchStartPos, match.length(0), replace);

        if (matchStartPos < str.length() && str.at(matchStartPos) == '\0')
        {
            str.erase(matchStartPos, 1);
        }
    }

    return str;
}

std::string DaVinCppString::fmtTime(msc duration)
{
    min minutes      = std::chrono::duration_cast<min>(duration);
    sec seconds      = std::chrono::duration_cast<sec>(duration);
    msc milliseconds = duration - seconds;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes.count() << ":" << std::setfill('0')
        << std::setw(2) << seconds.count() << "." << std::setfill('0') << std::setw(2)
        << milliseconds.count();

    return oss.str();
}

std::string DaVinCppString::fmtTime(sec duration)
{
    min minutes = std::chrono::duration_cast<min>(duration);
    sec seconds = duration - minutes;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes.count() << ":" << std::setfill('0')
        << std::setw(2) << seconds.count();

    return oss.str();
}
}  // namespace davincpp
