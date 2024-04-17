#pragma once

#include <cppJify/CppJify.hpp>

namespace cppJify {

    CppJify::CppJify(const std::string& p_basePackage, const std::string& p_baseClassname)
        : _jniComposer(p_basePackage, p_baseClassname) {}

}  // namespace cppJify