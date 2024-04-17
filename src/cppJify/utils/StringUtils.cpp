#pragma once

#include <cppJify/CppJifyConstants.hpp>
#include <cppJify/utils/StringUtils.hpp>

namespace cppJify::utils {

    void replaceAll(std::string& source, const std::string& from, const std::string& to) {
        if (from.empty()) {
            return;  // Prevents infinite loop if 'from' is an empty string
        }

        size_t startPos = 0;
        while ((startPos = source.find(from, startPos)) != std::string::npos) {
            source.replace(startPos, from.length(), to);
            startPos += to.length();  // Handles the case where 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    const std::string JIFY_TRANSFORM(std::string& p_jniSrc, const size_t p_argId, const std::string& p_ctype) {
        replaceAll(p_jniSrc, JIFY_PLACEHOLDER_CTYPE, p_ctype);
        replaceAll(p_jniSrc, "$" + JIFY_PLACEHOLDER_J_ARG, JIFY_PLACEHOLDER_J_ARG + std::to_string(p_argId));
        replaceAll(p_jniSrc, "$" + JIFY_PLACEHOLDER_C_ARG, JIFY_PLACEHOLDER_C_ARG + std::to_string(p_argId));

        return p_jniSrc;
    }

    const std::string JIFY_TRANSFORM(std::string& p_jniSrc, const std::string& p_func, const std::string& p_ctype) {
        replaceAll(p_jniSrc, JIFY_PLACEHOLDER_CTYPE, p_ctype);
        replaceAll(p_jniSrc, JIFY_PLACEHOLDER_FUNC, p_func);

        return p_jniSrc;
    }

}  // namespace cppJify::utils