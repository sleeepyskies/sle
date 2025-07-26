#pragma once

#include <string>

namespace sle {

/// @brief Trims any whitespace from the beginning of a string
inline std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isspace(c); }));
    return s;
}

/// @brief Trims any whitespace from the end of a string
inline std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    return s;
}

/// @brief Trims any whitespace from the beginning and the end of a string
inline std::string& trim(std::string& s) { return ltrim(rtrim(s)); }

} // namespace sle
