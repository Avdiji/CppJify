#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // bool
    template <>
    class JifyMapper<bool> {
        public:
            static const std::string CType() { return "bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jboolean>({});), functionCall);
            }
    };

    // const bool
    template <>
    class JifyMapper<const bool> {
        public:
            static const std::string CType() { return "const bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<const bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jboolean>({});), functionCall);
            }
    };

    // bool& -> handle it like a regular bool since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<bool&> {
        public:
            static const std::string CType() { return "bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<bool>({});), functionCall);
            }
    };

    // const bool&
    template <>
    class JifyMapper<const bool&> {
        public:
            static const std::string CType() { return "const bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<const bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jboolean>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
