#pragma once

#include <string>

namespace cppJify::utils {

    void replaceAll(std::string& source, const std::string& from, const std::string& to);

    [[nodiscard]] const std::string JIFY_TRANSFORM(std::string& p_jniSrc,
                                                   const size_t p_argId,
                                                   const std::string& p_ctype = "");

    [[nodiscard]] const std::string JIFY_TRANSFORM(std::string& p_jniSrc,
                                                   const std::string& p_func,
                                                   const std::string& p_ctype = "");

}  // namespace cppJify::utils