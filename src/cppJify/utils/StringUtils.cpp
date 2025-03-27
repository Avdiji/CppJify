#include <cppJify/utils/StringUtils.hpp>
#include <regex>
#include <string>

namespace cppJify::utils {
    std::string replaceAll(const std::string& original, const std::string& toReplace, const std::string& replacement) {
        const std::string escapedToReplace = std::regex_replace(toReplace, std::regex(R"([\$\^\*\+\?\.\(\)\[\]\{\}\\\|])"), R"(\$&)");
        const std::regex pattern(escapedToReplace);

        return std::regex_replace(original, pattern, replacement);
    }
}  // namespace cppJify::utils
