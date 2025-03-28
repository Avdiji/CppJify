#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // float
    template <>
    class JifyMapper<float> {
        public:
            static const std::string CType() { return "float"; }
            static const std::string JniType() { return "jfloat"; }
            static const std::string JavaType() { return "float"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<float>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jfloat>({});), functionCall);
            }
    };

    // const float
    template <>
    class JifyMapper<const float> {
        public:
            static const std::string CType() { return "const float"; }
            static const std::string JniType() { return "jfloat"; }
            static const std::string JavaType() { return "float"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<const float>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jfloat>({});), functionCall);
            }
    };

    // float& -> handle it like a regular float since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<float&> {
        public:
            static const std::string CType() { return "float"; }
            static const std::string JniType() { return "jfloat"; }
            static const std::string JavaType() { return "float"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<float>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jfloat>({});), functionCall);
            }
    };

    // const float&
    template <>
    class JifyMapper<const float&> {
        public:
            static const std::string CType() { return "const float"; }
            static const std::string JniType() { return "jfloat"; }
            static const std::string JavaType() { return "float"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<const float>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jfloat>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
