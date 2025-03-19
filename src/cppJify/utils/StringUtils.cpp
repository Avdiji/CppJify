#pragma once

#include <cppJify/utils/StringUtils.hpp>
#include <regex>

namespace cppJify::utils {
    std::string replaceAll(const std::string& original, const std::string& toReplace, const std::string& replacement) {
        std::regex pattern(toReplace);
        return std::regex_replace(original, pattern, replacement);
    }
}  // namespace cppJify::utils