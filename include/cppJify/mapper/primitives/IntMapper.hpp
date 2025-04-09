#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // int
    template <>
    class JifyMapper<int> {
        public:
            static const std::string CType() { return "int"; }
            static const std::string JniType() { return "jint"; }
            static const std::string JavaType() { return "int"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tint {} = static_cast<int>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jint>({});), functionCall);
            }
    };

    // const int
    template <>
    class JifyMapper<const int> {
        public:
            static const std::string CType() { return "const int"; }
            static const std::string JniType() { return "jint"; }
            static const std::string JavaType() { return "int"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst int {} = static_cast<const int>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jint>({});), functionCall);
            }
    };

    // int& -> handle it like a regular int since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<int&> {
        public:
            static const std::string CType() { return "int"; }
            static const std::string JniType() { return "jint"; }
            static const std::string JavaType() { return "int"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tint {} = static_cast<int>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jint>({});), functionCall);
            }
    };

    // const int&
    template <>
    class JifyMapper<const int&> {
        public:
            static const std::string CType() { return "const int"; }
            static const std::string JniType() { return "jint"; }
            static const std::string JavaType() { return "int"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst int {} = static_cast<const int>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jint>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
