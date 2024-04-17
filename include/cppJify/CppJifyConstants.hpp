#pragma once

#include <string>

#define JIFY_OVERLOADED_FUNC(ReturnType, FUNC, ...) static_cast<ReturnType (*)(__VA_ARGS__)>(FUNC)
#define JIFY_RAW(code) std::string(#code)

namespace cppJify {

    // Prefixes / Suffixes
    static const std::string JIFY_JAVA_PREFIX = "Java_";
    static const std::string JIFY_JNI_SUFFIX = "_JIFY__";  // TODO research jni suffixes

    // Placeholder
    static const std::string JIFY_PLACEHOLDER_C_ARG = "carg";
    static const std::string JIFY_PLACEHOLDER_J_ARG = "jarg";
    static const std::string JIFY_PLACEHOLDER_FUNC = "$func";
    static const std::string JIFY_PLACEHOLDER_CTYPE = "$ctype";

}  // namespace cppJify