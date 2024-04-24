#pragma once

#include <cppJify/CppJify.hpp>

namespace cppJify {

    CppJify::CppJify(const std::string& p_basePackage, const std::string& p_baseClassname)
        : _jniApi(p_basePackage, p_baseClassname) {}

    void CppJify::include(const std::string& p_cIncludePath) { _jniApi.include(p_cIncludePath); }

    void CppJify::generateApiFiles() {
        _jniApi.generateJniApi();
    }

}  // namespace cppJify