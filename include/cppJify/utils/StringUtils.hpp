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

}  // namespace cppJify::utils