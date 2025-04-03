#include <cppJify/utils/StringUtils.hpp>
#include <regex>
#include <string>

namespace cppJify::utils {
    std::string replaceAll(const std::string& original, const std::string& toReplace, const std::string& replacement) {
        const std::string escapedToReplace = std::regex_replace(toReplace, std::regex(R"([\$\^\*\+\?\.\(\)\[\]\{\}\\\|])"), R"(\$&)");
        const std::regex pattern(escapedToReplace);

        return std::regex_replace(original, pattern, replacement);
    }

    unsigned int countSubstringInString(const std::string& string, const std::string& substring) {
        if (substring.empty()) return 0;

        unsigned int count = 0;
        size_t pos = 0;

        while ((pos = string.find(substring, pos)) != std::string::npos) {
            ++count;
            ++pos;  // Move forward to allow overlapping substrings
        }
        return count;
    }

}  // namespace cppJify::utils
