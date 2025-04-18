#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // char
    template <>
    class JifyMapper<char> {
        public:
            static const std::string CType() { return "char"; }
            static const std::string JniType() { return "jchar"; }
            static const std::string JavaType() { return "char"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tchar {} = static_cast<char>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jchar>({});), functionCall);
            }
    };

    // const char
    template <>
    class JifyMapper<const char> {
        public:
            static const std::string CType() { return "const char"; }
            static const std::string JniType() { return "jchar"; }
            static const std::string JavaType() { return "char"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst char {} = static_cast<const char>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jchar>({});), functionCall);
            }
    };

    // char& -> handle it like a regular char since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<char&> {
        public:
            static const std::string CType() { return "char"; }
            static const std::string JniType() { return "jchar"; }
            static const std::string JavaType() { return "char"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tchar {} = static_cast<char>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jchar>({});), functionCall);
            }
    };

    // const char&
    template <>
    class JifyMapper<const char&> {
        public:
            static const std::string CType() { return "const char"; }
            static const std::string JniType() { return "jchar"; }
            static const std::string JavaType() { return "char"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst char {} = static_cast<const char>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jchar>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
