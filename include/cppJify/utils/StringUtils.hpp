#pragma once
#include <string>

namespace cppJify::utils {

    /**
     * Replace all substring in (toReplace) in original.
     *
     * @param original The original String.
     * @param toReplace The substring to be replaced.
     * @param replacement The replacement.
     *
     * @return A new String where all occurences of the given substring have been replaced.
     */
    std::string replaceAll(const std::string& original, const std::string& toReplace, const std::string& replacement);

    /**
     * Count the occurences of a substring within a string
     *
     * @param string The string containing the substring.
     * @param substring The substring to count the occurences of.
     */
    unsigned int countSubstringInString(const std::string& string, const std::string& substring);

}  // namespace cppJify::utils